<?php
function rhe_allotment_update($allotment_type, $estate_id) {
    if(!empty($allotment_type) && !empty($estate_id)) {        
        rhe_allotment_update_vs($allotment_type, $estate_id);
        drupal_goto("/rhe_allotment");
    }
}

function rhe_allotment_update_vs($allotment_type, $estate_id) {    
    $total_applicant = get_no_of_applicant_vs($allotment_type, $estate_id);
    if($total_applicant > 0) {
        $allotment_process_result = db_query("select * from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
        $no_of_rows = $allotment_process_result->rowCount();
        if($no_of_rows <= 0) {
            //$x = 1;
            $allotment_process_no = 'ALOT-01';
            $allotment_process_arr = array();
            $allotment_process_arr['allotment_process_no'] = $allotment_process_no;
            $allotment_process_arr['allotment_process_type']  = 'ALOT';
            $allotment_process_arr['allotment_flat_type']  = $allotment_type;

            db_insert('housing_allotment_process')
            ->fields($allotment_process_arr)
            ->execute();
        } else {
            $result_process_no = db_query("select max(substr(allotment_process_no, 6)) as allotment_process_no from {housing_allotment_process} where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
            $data_process_no = $result_process_no->fetchObject();
            $x = $data_process_no->allotment_process_no;
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
            
            $allotment_process_arr = array();
            $allotment_process_arr['allotment_process_no'] = $allotment_process_no;
            $allotment_process_arr['allotment_process_type']  = 'ALOT';
            $allotment_process_arr['allotment_flat_type']  = $allotment_type;

            db_insert('housing_allotment_process')
            ->fields($allotment_process_arr)
            ->execute();
        }

        $vacancy_details = get_vacancy_details($allotment_type, $estate_id, 'vs');
        /* echo '<pre>';
        print_r($vacancy_details);
        exit; */
        foreach($vacancy_details as $vacancy) {
            $estate_id = $vacancy['estate_id'];
            $flat_id = $vacancy['flat_id'];
            $flat_type_id = $vacancy['flat_type_id'];
            
			//fetching applicant according seniority
            $result = db_query("select hoa.online_application_id, hca.flat_type_id, hca.occupation_estate, hca.occupation_flat from {housing_online_application} as hoa
            inner join {housing_applicant_official_detail} as haod on haod.applicant_official_detail_id = hoa.applicant_official_detail_id
            inner join {housing_vs_application} as hca on hca.online_application_id = hoa.online_application_id
            where hoa.status = 'verified' and hca.occupation_estate = $estate_id and hca.flat_type_id = $flat_type_id
            order by hoa.online_application_id ASC limit 1");
            
            $data = $result->fetchObject();
	
            if($result->rowCount() > 0) {
                
                $allotment_upd_arr = array();
                $allotment_upd_arr['status']  = 'allotted';
                //$allotment_upd_arr['online_application_id']  = $data->online_application_id;	//commented off on 15.04.2023 because this line is not required
            
                db_update('housing_online_application')
                ->fields($allotment_upd_arr)
                //->condition('online_application_id', $allotment_upd_arr['online_application_id'])	//commented off on 15.04.2023 because this line is not required
                ->condition('online_application_id', $data->online_application_id)
                ->execute();
                
                //update new flat which allotted to applicant
                db_update('housing_flat')
                ->fields(array(
                            'flat_status_id' => 2
                        ))
                ->condition('flat_id', $flat_id)
                ->execute();
                
                //update old flat where applicant stay
                /*db_update('housing_flat')
                ->fields(array(
                            'flat_status_id' => 1
                        ))
                ->condition('flat_id', $data->occupation_flat)
                ->execute();*/
                
                $allotment_process_no = db_query("select max(allotment_process_no) as allotment_process_no from {housing_allotment_process} 
                                                    where allotment_process_type = :allotment_process_type", array(':allotment_process_type' => 'ALOT'));
                $data_process_no = $allotment_process_no->fetchObject();
                
                $allotment_ins_arr = array();
                $allotment_ins_arr['online_application_id']  = $data->online_application_id;
                $allotment_ins_arr['flat_id']  = $flat_id;
                $allotment_ins_arr['allotment_no'] = 'CSAL-'.$data->online_application_id.'-'.date("dmY");
                $allotment_ins_arr['allotment_process_no'] = $data_process_no->allotment_process_no;
            
                db_insert('housing_flat_occupant')
                ->fields($allotment_ins_arr)
                ->execute();                    
            }
        }
    }
}