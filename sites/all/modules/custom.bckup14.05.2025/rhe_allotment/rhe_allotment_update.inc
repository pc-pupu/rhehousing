<?php
function rhe_allotment_update($allotment_type='', $district_code=0) {    
    if(!empty($allotment_type)) {  
        $all_vacant_estates = get_estatewise_vacancy($allotment_type,$district_code);
         
        $transaction = db_transaction();
        try {
            $get_allot_process_no = update_housing_allotment_process($allotment_type);
            foreach($all_vacant_estates as $estate)  { // For each estate floor and category shifting is performed
                $estate_id = $estate -> estate_id;
                update_rhe_allotment_vs($allotment_type, $estate_id, $district_code);
                update_rhe_allotment_cs($allotment_type, $estate_id, $district_code);
            }  // End of floor & category shifting
            
            //update_rhe_allotment_new($allotment_type, $district_code); // Allotment for new applicant after completion of floor & category shifting
            update_rhe_allotment_new($allotment_type, $district_code);
            drupal_set_message('Allotment Process Completed Successfully with Process No '.$get_allot_process_no);
            drupal_goto("/rhe_allotment");

        } catch (Exception $e) {
            $transaction->rollback();
            watchdog_exception('rhe_allotment', $e);
        }    
    }
}

function update_rhe_allotment_vs($allotment_type, $estate_id, $district_code = 0) {    
    $total_applicant = get_no_of_applicant_vs($allotment_type, $estate_id);
    if($total_applicant > 0) {
        $vacancy_details = get_vacancy_details($allotment_type, $estate_id, 'vs', $district_code);
        if(count($vacancy_details) > 0) {
            foreach($vacancy_details as $vacancy) {
                $flat_id = $vacancy['flat_id'];
                $flat_type_id = $vacancy['flat_type_id'];
                
                //fetching applicant according seniority
                $result = get_applicant($estate_id, $flat_type_id, 'vs');
        
                if($result->rowCount() > 0) {
                    $applicant = $result->fetchObject();
                    update_housing_online_application($applicant -> online_application_id);
                    update_housing_flat($flat_id);
                    update_housing_flat_occupant($flat_id, $applicant -> online_application_id, 'VSAL');           
                }
            }
        }
    }
}
function update_rhe_allotment_cs($allotment_type, $estate_id, $district_code = 0) {
    $total_applicant = get_no_of_applicant_cs($allotment_type, $estate_id);
    $cs_alloted_counter = 1; // count the applicant who allotted between 1st to 10th floor
    if($total_applicant > 0) {
        // checking for any vacancy between 1st to 10th floor after floor shifting allotment
        $vacancy_details_vs = get_vacancy_details($allotment_type, $estate_id, 'vs', $district_code);
        $count_vacancy_details_vs = count($vacancy_details_vs);
        if($count_vacancy_details_vs > 1) { // if total vacancy between 1st to 10th floor is greater than 1
            // get 40% of vacancy between 1st to 10th floor after allotment for floor shifting
            $cs_count_from_vs = round($count_vacancy_details_vs * 0.4);

            // Start ----- Allot 40% of remaining between 1st to 10th floor vacancy for category shifting.
            foreach($vacancy_details_vs as $vacancy) {
                if($cs_alloted_counter > $cs_count_from_vs) {
                    break;
                }
                $flat_id = $vacancy['flat_id'];
                $flat_type_id = $vacancy['flat_type_id'];

                //fetching applicant according seniority
                $result = get_applicant($estate_id, $flat_type_id, 'cs');
        
                if($result->rowCount() > 0) {
                    $applicant = $result->fetchObject();
                    update_housing_online_application($applicant -> online_application_id);
                    update_housing_flat($flat_id);
                    update_housing_flat_occupant($flat_id, $applicant -> online_application_id, 'CSAL');           
                }                
                $cs_alloted_counter++;
            }
            // End ----- Allot between 1st to 10th floor vacancy for category shifting.
        }        
    }
    // Start -----  Allot ground & top floor vacancy for category shifting.
    if(--$cs_alloted_counter < $total_applicant) { // if applicant remains after alloted at 1st to 10th floor.
        $vacancy_details = get_vacancy_details($allotment_type, $estate_id, 'cs', $district_code);
        if(count($vacancy_details) > 0) {
            foreach($vacancy_details as $vacancy) {
                $flat_id = $vacancy['flat_id'];
                $flat_type_id = $vacancy['flat_type_id'];
                
                //fetching applicant according seniority
                $result = get_applicant($estate_id, $flat_type_id, 'cs');
        
                if($result->rowCount() > 0) {
                    $applicant = $result->fetchObject();
                    update_housing_online_application($applicant -> online_application_id);
                    update_housing_flat($flat_id);
                    update_housing_flat_occupant($flat_id, $applicant -> online_application_id, 'CSAL');           
                }
            }
        }        
    }
    // End -----  Allot ground & top floor vacancy for category shifting.
}
function update_rhe_allotment_new($allotment_type, $district_code = 0) {    
    $roaster_counter_start = 1; $roaster_counter_end = 29; 
    $applicant_allotted_counter = 0; $vacancy_filled_counter = 0; 
    $total_applicant = get_no_of_applicant_new($allotment_type);
    $total_vacancy = get_total_vacancy_new($allotment_type, $district_code );
    // $next_roaster_counter = get_next_roaster_counter($allotment_type); //old code by prasenjit turned off 04-11-2024
    // $j=0;
    while($applicant_allotted_counter < $total_applicant) {
        $next_roaster_counter = get_next_roaster_counter($allotment_type); //04-11-2024
        //while(true) removed as it causes infinite looping when vacancy exhausts 03-11-2024
        while(true) {   
            //fetching applicant according roaster and seniority
            // $applicant_result = get_applicant_new($allotment_type, $next_roaster_counter);// old code by prasenjit// turned off 30-10-2024
            $f_applicant_result = get_applicant_new($allotment_type, $next_roaster_counter);
            //print_r($f_applicant_result);die;
            $applicant_result  = $f_applicant_result['result'];
            //print_r($applicant_result->rowCount());die;

            if($applicant_result -> rowCount() > 0) {
                $vacancy = array();
                $applicant = $applicant_result -> fetchObject();
                //print_r($applicant);die;
                // Vacancy fetching starts
                // Fetch vacancy according to preference if any
                $vacancy_on_preference = get_vacancy_on_preference($allotment_type, $applicant -> online_application_id, $district_code);
                
                if($vacancy_on_preference -> rowCount() > 0) {
                    $vacancy = $vacancy_on_preference -> fetchObject();
                } else { // Fetch vacancy from all vacant flat with the order F,S,G,T if no vacancy according to preference
                    $vacancy_general = get_vacancy_details_new($allotment_type,$district_code );
                    
                    if($vacancy_general -> rowCount() > 0) {
                        $vacancy = $vacancy_general -> fetchObject();
                    }
                }
                //print_r($vacancy);die;
                //code added 03-11-2024 to handle situations when vacancy is not available
                if(empty($vacancy)){
                    $applicant_allotted_counter = $applicant_allotted_counter + 1;
                    break;
                }

                //end 

                //print_r($applicant);echo'dd';print_r( $vacancy);die;               
                $flat_id = $vacancy -> flat_id;
                $flat_type_id = $vacancy -> flat_type_id;
                // Vacancy fetching ends
                update_housing_online_application($applicant -> online_application_id);
                update_housing_flat($flat_id);
                $flat_occupant_id = update_housing_flat_occupant($flat_id, $applicant -> online_application_id, 'NAL');//05-07-2024 returning flat_occupant_id
                //echo $flat_occupant_id;die();
                if($f_applicant_result['is_spl_recomended']==1){
                    
                    $update_stat=update_housing_special_recommendation($applicant -> online_application_id); //30-10-2024 update speacial recommendation table  
                }
               
                update_housing_allotment_roaster_counter($allotment_type, $next_roaster_counter);
                update_housing_allotment_roaster_details($allotment_type, $next_roaster_counter, $applicant -> allotment_category,$flat_occupant_id);//05-07-2024 adding flat_occupant_id

                $applicant_allotted_counter = $applicant_allotted_counter + 1;
                //print_r($applicant_allotted_counter);die;
                //$vacancy_filled_counter = $vacancy_filled_counter + 1;
                
                //break removed as the while(true) loop above is removed(it causes infinite looping when vacancy exhausts) 03-11-2024
                break;
            } else {
                //echo $next_roaster_counter;echo 'rc'.$roaster_counter_end; die;
                if($next_roaster_counter < $roaster_counter_end) {
                    $next_roaster_counter = $next_roaster_counter + 1;
                } else {
                    $next_roaster_counter = $roaster_counter_start;
                }

                //03-11-2024 added to prevent infinite loop
                //$applicant_allotted_counter = $applicant_allotted_counter + 1;
                //break;
            }
        }//echo 'fffff';die;
        /* if($applicant_allotted_counter > $total_applicant || $vacancy_filled_counter > $total_vacancy) {
            break;
        }  */       
    }//$j++;return $j;
}
function update_housing_allotment_process($allotment_type) {

    $allotment_process_arr = array();
    $allotment_process_no = get_next_allotment_process_no($allotment_type);

    $allotment_process_arr['allotment_process_no'] = $allotment_process_no;
    $allotment_process_arr['allotment_process_type']  = 'ALOT';
    $allotment_process_arr['allotment_flat_type']  = $allotment_type;    

    $get_last_id = db_insert('housing_allotment_process')   //added $get_last_id by debaleena 
        ->fields($allotment_process_arr)
        ->execute();


    //////////// debaleena start 24.07.2024////////////////////
    $get_process_no = db_query("select allotment_process_no from housing_allotment_process
                                    where allotment_process_id = " . $get_last_id);

    $get_process_no = $get_process_no->fetchObject()->allotment_process_no;
    //echo $get_process_no;die;
    return $get_process_no;   

    ///////////////////end///////////////////// 

        
}
function update_housing_online_application($online_application_id) {
    global $user;
    $allotment_upd_arr = array();
    $allotment_upd_arr['status']  = 'allotted';
    $allotment_upd_arr['date_of_verified']  = date('Y-m-d H:i:s'); // Done by Subham 25-11-2024
    //$allotment_upd_arr['online_application_id']  = $data->online_application_id;	//commented off on 15.04.2023 because this line is not required
    db_update('housing_online_application')
    ->fields($allotment_upd_arr)
    //->condition('online_application_id', $allotment_upd_arr['online_application_id'])	//commented off on 15.04.2023 because this line is not required
    ->condition('online_application_id', $online_application_id)
    ->execute();

    //code by moumita 06-06-2024
    $process_flow_upd_arr = array(
        'status_id'  => 6,
        'online_application_id' => $online_application_id,
        'uid' => $user->uid,
        'short_code' => $allotment_upd_arr['status'],
        'created_at' => date('Y-m-d H:i:s')
     );
    db_insert('housing_process_flow')
    ->fields($process_flow_upd_arr)
    ->execute();
}
function update_housing_flat($flat_id) {//echo $flat_id;die;
    //update new flat which allotted to applicant
    db_update('housing_flat')
    ->fields(array(
                // 'flat_status_id' => 2 //turned off 30-10-2024 
                'flat_status_id' => 7 // from "occupied=>2" to "alloted=>7" 30-10-2024
            ))
    ->condition('flat_id', $flat_id)
    ->execute();
}
function update_housing_flat_occupant($flat_id, $online_application_id, $allotment_no_prefix) {
    $allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} 
    where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
    $data_process_no = $allotment_process_no->fetchObject();

    $allotment_ins_arr = array();
    $allotment_ins_arr['online_application_id']  = $online_application_id;
    $allotment_ins_arr['flat_id']  = $flat_id;
    $allotment_ins_arr['allotment_no'] = $allotment_no_prefix . '-' . $online_application_id . '-' . date("dmY");
    $allotment_ins_arr['allotment_process_no'] = $data_process_no -> allotment_process_no;

    db_insert('housing_flat_occupant')
    ->fields($allotment_ins_arr)
    ->execute();   

    // 05-07-2024
    $query = db_select('housing_flat_occupant', 'hfa');
    $query->addExpression('MAX(flat_occupant_id)','flat_occupant_id');
    $result =$query->execute();
    $data = $result->fetchObject();

    return $data->flat_occupant_id;
    //end
}
function update_housing_allotment_roaster_counter($allotment_type, $next_roaster_counter) {
    if(!empty($allotment_type) && !empty($next_roaster_counter)) {
        db_insert('housing_allotment_roaster_counter')
	        ->fields(
                array(
                    'allotment_type' => $allotment_type, 
                    'last_roaster_counter' => $next_roaster_counter
                )
            ) ->execute();
    }    	
}
function update_housing_allotment_roaster_details($allotment_type, $next_roaster_counter, $allotment_category,$flat_occupant_id) {
    $allotment_roaster_details_arr = array(); $allotment_process_no = "";
    $result = db_query("select allotment_process_no from housing_allotment_process
    where allotment_flat_type = " . $allotment_type . "
    ORDER BY allotment_process_id DESC
    limit 1");
    if($result -> rowCount() > 0) {
        $record = $result -> fetchObject();
        $allotment_process_no = $record -> allotment_process_no;
    }
    $allotment_roaster_details_arr['allotment_process_no']  = $allotment_process_no;
    $allotment_roaster_details_arr['allotment_flat_type']  = $allotment_type;
    $allotment_roaster_details_arr['roaster_vacancy_position'] = $next_roaster_counter;
    $allotment_roaster_details_arr['allotment_reason'] = $allotment_category;
    $allotment_roaster_details_arr['roaster_list_no'] = NULL;
    //$allotment_roaster_details_arr['flat_occupant_id'] = NULL; /////by prasenjit
    $allotment_roaster_details_arr['flat_occupant_id'] = $flat_occupant_id;// 05-07-2024 

    db_insert('housing_allotment_roaster_details')
    ->fields($allotment_roaster_details_arr)
    ->execute();
}
function get_applicant($estate_id, $flat_type_id, $shifting_type) {
    $shifting_applicant_table = array(
        'vs' => 'housing_vs_application',
        'cs' => 'housing_cs_application',
    );

    $result = db_query("select hoa.online_application_id, hca.flat_type_id, hca.occupation_estate, hca.occupation_flat from {housing_online_application} as hoa
    inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
    inner join {" . $shifting_applicant_table[$shifting_type] . "} as hca on hca.online_application_id = hoa.online_application_id
    where hoa.status = 'housingapprover_approved_1' and hca.occupation_estate = $estate_id and hca.flat_type_id = $flat_type_id
    order by hoa.online_application_id ASC limit 1"); //before(done by prasenjit)   housing_sup_approved_1 to housingapprover_approved_1 by debaleena 04-09-2024
    //order by hoa.computer_serial_no ASC limit 1");// after (done by Moumita)

    return $result;
}
function get_vacancy_on_preference($flat_type_id, $online_application_id, $district_code = 0) {
    $result = db_query("SELECT t1.* FROM housing_flat AS t1
    INNER JOIN housing_estate AS t2 ON t1.estate_id = t2.estate_id
    INNER JOIN housing_district AS t3 ON t2.district_code = t3.district_code
    INNER JOIN (select preference_order, estate_id from housing_new_application_estate_preferences
    where online_application_id = " . $online_application_id . "
    ORDER BY preference_order ASC
    limit 3) as t4 ON t2.estate_id = t4.estate_id
    WHERE t1.flat_type_id = " . $flat_type_id . "
    AND t1.flat_status_id = 1
    AND t3.district_code = ".$district_code."
    ORDER BY t4.preference_order, t1.flat_id
    limit 1");

    return $result;
}
function get_vacancy_details_new($flat_type_id, $district_code = 0) {
    $result = db_query("SELECT t1.* FROM housing_flat AS t1
    INNER JOIN housing_estate AS t2 ON t1.estate_id = t2.estate_id
    INNER JOIN housing_district AS t3 ON t2.district_code = t3.district_code
    WHERE t1.flat_type_id = " . $flat_type_id . "
    AND t1.flat_status_id = 1    
    AND t3.district_code = ".$district_code."
    ORDER BY CASE
        when t1.floor = 'First' then 1
        when t1.floor = 'Second' then 2
        when t1.floor = 'Third' then 3
        when t1.floor = 'Fourth' then 4
        when t1.floor = 'Fifth' then 5
        when t1.floor = 'Sixth' then 6
        when t1.floor = 'Seventh' then 7
        when t1.floor = 'Eighth' then 8
       
        when t1.floor = 'Ground' then 9
        when t1.floor = 'Top' then 10
        END, 
        t1.floor");

        // last seen by Group 06-06-2024
        //G+9 added by debaleena 12-09-2024

    return $result;
}
function get_next_roaster_counter($flat_type_id) {
	$roaster_counter_start = 1; $roaster_counter_end = 29; 
	$next_roaster_counter = $roaster_counter_start;

    $result_roaster_counter = db_query("select last_roaster_counter from housing_allotment_roaster_counter where allotment_type = " . $flat_type_id . " order by id desc limit 1");

    if($result_roaster_counter->rowCount() > 0) {
		$data_counter = $result_roaster_counter -> fetchObject();
		$last_roaster_counter = $data_counter -> last_roaster_counter;

		if($last_roaster_counter < $roaster_counter_end) {
			$next_roaster_counter = $last_roaster_counter + 1;
		}		
	}

	return $next_roaster_counter;
}

function get_applicant_new($flat_type_id, $next_roaster_counter) {
    $roaster_tbl = ""; 
    $is_spl_recomended = 0; // 29-10-2024 special recommendation
    switch($flat_type_id) { // 1=>A, 2=>B, 3=>C, 4=>D, 5=> A+ // changed by Moumita 06-06-2024
        case 1:
        case 2:
            $roaster_tbl = "housing_roaster4ab_master"; // housing_roaster4b_master
            break;
        case 3:
        case 4:
            $roaster_tbl = "housing_roaster4cd_master";
            break;
        case 5:
            $roaster_tbl = "housing_roasterAplus_master"; // housing_roaster4a_aplus_master
            break;
    }

    // 29-10-2024 special recommendation
    
    //$roaster_category=db_query("select category from". $roaster_tbl . "where counter =" . $next_roaster_counter );
    
    $query = db_select($roaster_tbl,'tbl');
    $query->addField('tbl', 'category');
    $query->condition('tbl.counter',$next_roaster_counter,'=');
    $result = $query->execute();
    $roaster_category = $result->fetchObject();
    //print_r($roaster_category->category);die;
    
    if($roaster_category->category == 'Recommended'){
        $query = db_query("select * from housing_special_recommended  ORDER BY priority_order ASC");
        //print_r($query->rowCount());die;
        $spl_recommended_datas = $query->fetchObject();
        if($query->rowCount() > 0){
            
            $spl_recommended_applicant = db_query("select * from housing_special_recommended  ORDER BY priority_order ASC limit 1");
            $spl_recommended_applicant=$spl_recommended_applicant->fetchObject();
            //print_r($spl_recommended_applicant->housing_online_application_id);die;

            $result = db_query("select * from housing_online_application as t1
            INNER JOIN housing_new_allotment_application as t2 on t1.online_application_id = t2.online_application_id
            WHERE t1.status = 'housingapprover_approved_1'  
            and t2.flat_type_id = " . $flat_type_id . "
            and t1.online_application_id = " . $spl_recommended_applicant->housing_online_application_id  . "
            ORDER BY t1.computer_serial_no ASC
            limit 1");
            $is_spl_recomended = 1;
            //print_r($result->fetchObject());die;
        }else{
            $result = db_query("select * from housing_online_application as t1
            INNER JOIN housing_new_allotment_application as t2 on t1.online_application_id = t2.online_application_id
            WHERE t1.status = 'housingapprover_approved_1'  
            and t2.flat_type_id = " . $flat_type_id . "
            and t2.allotment_category = (select category from " . $roaster_tbl . " where counter = " . $next_roaster_counter . ")
            ORDER BY t1.computer_serial_no ASC
            limit 1");
            $is_spl_recomended=0;
            //print_r($result);die;
        }
    }else{

        $result = db_query("select * from housing_online_application as t1
        INNER JOIN housing_new_allotment_application as t2 on t1.online_application_id = t2.online_application_id
        WHERE t1.status = 'housingapprover_approved_1'  
        and t2.flat_type_id = " . $flat_type_id . "
        and t2.allotment_category = (select category from " . $roaster_tbl . " where counter = " . $next_roaster_counter . ")
        ORDER BY t1.computer_serial_no ASC
        limit 1");
        $is_spl_recomended=0;
    }

    //end

    // previous code without special recommendation . Turned off on 30-10-2024
    
    /*$result = db_query("select * from housing_online_application as t1
    INNER JOIN housing_new_allotment_application as t2 on t1.online_application_id = t2.online_application_id
    WHERE t1.status = 'housingapprover_approved_1'  
    and t2.flat_type_id = " . $flat_type_id . "
    and t2.allotment_category = (select category from " . $roaster_tbl . " where counter = " . $next_roaster_counter . ")
    ORDER BY t1.computer_serial_no ASC
    limit 1");*/
    // ORDER BY t1.online_application_id ASC
    // housing_sup_approved_1 to housingapprover_approved_1 by debaleena 04-09-2024
    //echo 'ff';print_r($result);die;
    
    $f_result=array(
        'is_spl_recomended'=>$is_spl_recomended,
        'result'=> $result
    );
    //echo'ff';print_r($f_result);die;

    return $f_result;
}
function get_next_allotment_process_no($allotment_type) {
    $allotment_process_result = db_query("select * from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
    $allotment_process_no = 'ALOT-01';
    if($allotment_process_result -> rowCount() > 0) {
        $result_process_no = db_query("select max(substr(allotment_process_no, 6)) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
        $data_process_no = $result_process_no -> fetchObject();
        $x = $data_process_no -> allotment_process_no;
        if($x < 9) {
            $x = $x + 1;
            $allotment_process_no = $x;
            $allotment_process_no = 'ALOT-0'.$allotment_process_no;
        }
        else {
            $x = $x + 1;
            $allotment_process_no = $x;
            $allotment_process_no = 'ALOT-'.$allotment_process_no;
        }
    }
    return $allotment_process_no;
}

//special recommendation 30-10-2024
function update_housing_special_recommendation($online_application_id){
    //echo'i am here';die;
    $spl_recommended_data = db_query("select * from housing_special_recommended
    WHERE  housing_online_application_id = " . $online_application_id);
    //print_r($spl_recommended_data->fetchObject());die;
    
    
        $spl_recommended_data = $spl_recommended_data->fetchObject();
        //echo'ff'.$spl_recommended_data->priority_order;die;

        //insert the spl recommended application in log table
        $housing_special_recommended_log_arr = array(
        'special_recommend_id'  => $spl_recommended_data->special_recommend_id,
        'housing_online_application_id' => $spl_recommended_data->housing_online_application_id,
        'priority_order' => $spl_recommended_data->priority_order,
        'flag' => 'alloted',
        'old_category'=>$spl_recommended_data->old_category,
        'new_category'=>$spl_recommended_data->new_category,
        'created_at_housing_special_recommended'=>$spl_recommended_data->created_at,
        'updated_at_housing_special_recommended'=>$spl_recommended_data->updated_at,
        'created_at' => date('Y-m-d H:i:s')
        );
  
        db_insert('housing_special_recommended_log')
        ->fields($housing_special_recommended_log_arr)
        ->execute();
        
        //delete the spl recommended application from spl recommended table  
        db_delete('housing_special_recommended')
        ->condition('special_recommend_id', $spl_recommended_data->special_recommend_id)
        ->execute();


        $applicant_priority_order = $spl_recommended_data->priority_order;
      

        $query = db_select('housing_special_recommended','hsr');
        $query->addExpression('MAX(priority_order)');
        $max= $query->execute()->fetchField();
        $max_order = ($max == '') ? '0' : $max;


        //update the priority order for rest of the datas present in spl recommended table
        for($i=$applicant_priority_order+1; $i<=$max_order; $i++){
            $spl_recommended_data = db_query("UPDATE housing_special_recommended SET priority_order = $i-1
            WHERE priority_order = $i");
        }
        
        return 0;
        //db_query("update housing_special_recommended set flag='alloted'
        //WHERE'  housing_online_application_id = " . $online_application_id);  
    
     
}
