<?php
function allotment_letter_flat_list($flat_type = '') {
	$query = db_select('housing_allotment_letter', 'hal');
	$query->addField('hal','flat_id');
	$query->condition('hal.flat_type',$flat_type,'=');
	$result = $query->execute();
	$flat_arr = array();
	while($data = $result->fetchObject()) {
		$flat_arr[] = $data->flat_id;
	}
	return $flat_arr;
}
function rhe_flat_allot_list_rst_estate_list($flat_type_id = 0, $status_id = 0, $estate_id = 0, $flat_list = NULL) {
	$query = db_select('housing_flat', 'hf');
	$query->addField('hf','flat_id');
	$query->addField('hf','flat_no');
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id',$flat_type_id,'=');
	$db_and->condition('hf.flat_status_id',$status_id,'=');
	$db_and->condition('hf.estate_id',$estate_id,'=');
	if(count($flat_list) > 0){
		$db_and->condition('hf.flat_id',$flat_list,'NOT IN');
	}
	$query->condition($db_and);
	$query->orderBy('flat_id', 'ASC');
	
	return $query->execute();
}
  function rhe_flat_generate_list($flat_type_id = 0, $status_id = 0, $flat_list = NULL) {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he',
		'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd',
		'he.district_code = hd.district_code');
		
	//$query->addField('hf', 'flat_id');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id',$flat_type_id,'=');
	$db_and->condition('hf.flat_status_id',$status_id,'=');
	if(count($flat_list) > 0){
		$db_and->condition('hf.flat_id',$flat_list,'NOT IN');
	}
	$query->condition($db_and);
	
	
	$query->groupBy('hf.estate_id');
	$query->groupBy('he.estate_name');
	$query->groupBy('he.estate_address');
	$query->groupBy('hd.district_name');
	$query->orderBy('district_name', 'ASC');
	$query->orderBy('estate_id', 'ASC');
	//$query->extend('TableSort')->extend('PagerDefault')->limit(1);
	
	return $query->execute();
}
function fetch_waiting_list($flat_type_id = 0){
	$flat_type = fetch_rhe_flat_name_rst_id($flat_type_id);
	$flat_ar = allotment_letter_flat_list($flat_type);
	$flat_status_id = fetch_flat_status_id('vacant');
	$result = rhe_flat_generate_list($flat_type_id,$flat_status_id,$flat_ar);
	$estate_list = array();
	 while($data = $result->fetchObject()) {
		 $flat_list_result = rhe_flat_allot_list_rst_estate_list($flat_type_id, $flat_status_id, $data->estate_id,$flat_ar);
		 $flat_list = array();
		 while($flat_list_data = $flat_list_result->fetchObject()) {
			 $flat_list[$flat_list_data->flat_id] = $flat_list_data->flat_no;
		 }
		 $estate_list[$data->estate_id] = array($data->estate_name => $flat_list);
		 $flat_list = NULL;
	 }
	
	$result1 = fetch_housing_application_data($flat_type_id);
	$result2 = fetch_housing_virtual_roaster_counter($flat_type_id);
	$housing_application_data = array();
	 while($data = $result1->fetchObject()) {
		$housing_application_data[] = $data;
	 }
	 
	 $housing_virtual_roaster_counter = array();
	 while($data1 = $result2->fetchObject()) {
		$housing_virtual_roaster_counter[$data1->category][] = $data1;
	 }
	  $data_array = array();

	 for( $i = 0; $i < count($housing_application_data); $i++){	
		 $obj = (array)fetch_roaster_counter($housing_virtual_roaster_counter, $housing_application_data[$i]->allotment_category);
		 if($obj == NULL){
			 $obj = array('roaster_counter' => 0,'list_no' => 0);
		 }
		 $cnt = $obj['roaster_counter'];
		 if($cnt > 0 && $cnt < 9){
			 $cnt = str_pad($cnt,2,"0",STR_PAD_LEFT);
		 }
	 	 $index = $obj['list_no'].$cnt;
		 
		 $application_type = $housing_application_data[$i]->application_type;
		 
		 $estate_choice_list = NULL;
		 if($application_type == 'New Allotment Application'){
				$estate_choice_list = fetch_appplicant_choice_list_for_estate($housing_application_data[$i]->online_application_id);
		 }
		
		 $choice_str = '<hr><label style="display:block;">Choice List</label>';
		 $j = 1;
		 foreach($estate_choice_list as $e_list){
			 if($j != 1)
			 	$choice_str.= '<br>';
			 $choice_str.= '<label>'.$j.'.</label>&nbsp;'.str_replace(' ','&nbsp;',$e_list);
			 $j++;
		 }
		 if($j == 1)
		 	$choice_str.= 'N/A';
	
		 $date = new DateTime($housing_application_data[$i]->date_of_application);
		 $data_array[$index]['applicant'] = '<h6><label class="label" style="color:#2F709B;letter-spacing: 0.06em;">'.str_replace(' ','&nbsp;',$housing_application_data[$i]->applicant_name).'</label><label style="color:#0090C7;font-weight: 400;display:block;">('.str_replace(' ','&nbsp;',$housing_application_data[$i]->allotment_category).')</label><div style="display:none;"><hr><label style="color:#0090C7;font-weight: 400;">'.str_replace(' ','&nbsp;',$application_type).'</label></div></h6>';
		 $data_array[$index]['roaster_counter'] = '<h6><b >'.$obj['roaster_counter'].' / List '.$obj['list_no'].'</b></h6>';
		 $data_array[$index]['rc'] = $obj['roaster_counter'];
		 $data_array[$index]['ln'] = $obj['list_no'];
		if($flat_type == 'A' || $flat_type == 'B'){
			  $data_array[$index]['grade_pay'] = '<h6 ><b >'.$housing_application_data[$i]->grade_pay.'</b></h6>';
		 }
		   $data_array[$index]['application_date'] = '<h6><b >'.$date->format('dS M,y').'</b></h6>';
		   $data_array[$index]['offer'] = $estate_choice_list;
		   //$data_array[$index]['choice'] = $choice_str;
		   $data_array[$index]['waiting_no'] = '';
		   $data_array[$index]['online_application_id'] = $housing_application_data[$i]->online_application_id;
		   $data_array[$index]['flat_offer'] = TRUE;
	   }
	   ksort($data_array);
	   $data_arr = array();
	   
	$i = 1; 
	foreach($data_array as $data_val){
		$flat_arr = allot_virtual_RHE($estate_list , $data_val['offer'] );
		$data_val['offer'] = '';
		if($flat_arr != NULL){
			$data_val['offer'] = '<h6><label class="label" >Flat:&nbsp;'.$flat_arr['flat_no'].'&nbsp;<label style="color:#0090C7;font-weight: 400;">[&nbsp;'.str_replace(' ','&nbsp;',$flat_arr['estate_name']).'&nbsp;]</label></label>';
			//<div style="display:none;">'.$data_val['choice'].'</div></h6>
			$data_val['flat_id'] = $flat_arr['flat_id'];
		}
		else{
			$data_val['flat_offer'] = FALSE;
		}
		
		$data_val['waiting_no'] = '<h6><span>'.$i++.'</span></h6>';
		$data_arr[$data_val['online_application_id']] = $data_val;
	}
	 
	 return $data_arr;
}



function fetch_housing_application_data($flat_type_id = 0){
		$flat_type = fetch_rhe_flat_name_rst_id($flat_type_id);
		$query = db_select('housing_application_data', 'had');
		$query->addField('had', 'application_type');
		$query->addField('had', 'online_application_id');
		$query->addField('had', 'date_of_application');
		$query->addField('had', 'applicant_name');
		$query->addField('had', 'grade_pay');
		$query->addField('had', 'allotment_category');
		$query->addField('had', 'flat_type');
		$query->addField('had', 'flat_type_id');
		$query->condition('had.flat_type',$flat_type,'=');
		$query->orderBy('flat_type','ASC');
		$query->orderBy('allotment_category','ASC');
		/*if($flat_type == 'A' || $flat_type == 'B'){
			$query->orderBy('grade_pay','DESC');
		}*/
		
		//echo $query; 
		
		return $query->execute();
	}
	
	
	function fetch_housing_virtual_roaster_counter($flat_type_id = 0){
		$flat_type = fetch_rhe_flat_name_rst_id($flat_type_id);
		$query = db_select('housing_virtual_roaster_counter', 'hvrc');
		$query->addField('hvrc', 'roaster_counter');
		$query->addField('hvrc', 'list_no');
		$query->addField('hvrc', 'category');
		$query->condition('hvrc.flat_type',$flat_type,'=');
		$query->orderBy('flat_type','ASC');
		$query->orderBy('category','ASC');
		$query->orderBy('list_no','ASC');
		$query->orderBy('roaster_counter','ASC');
		//echo $query; 
		return $query->execute();
	}
	
	function fetch_appplicant_choice_list_for_estate($online_application_id = 0){
		$query = db_select('housing_new_allotment_application', 'hna');
		$query->leftJoin('housing_estate', 'he1',
		'he1.estate_id = hna.estate_id_choice1');
		$query->leftJoin('housing_estate', 'he2',
		'he2.estate_id = hna.estate_id_choice2');
		$query->leftJoin('housing_estate', 'he3',
		'he3.estate_id = hna.estate_id_choice3');
		$query->leftJoin('housing_estate', 'he4',
		'he4.estate_id = hna.estate_id_choice4');
		$query->addField('hna', 'estate_id_choice1','choice1');
		$query->addField('hna', 'estate_id_choice2','choice2');
		$query->addField('hna', 'estate_id_choice3','choice3');
		$query->addField('hna', 'estate_id_choice4','choice4');
		$query->addField('he1', 'estate_name','choice1_estate_name');
		$query->addField('he2', 'estate_name','choice2_estate_name');
		$query->addField('he3', 'estate_name','choice3_estate_name');
		$query->addField('he4', 'estate_name','choice4_estate_name');
		$query->condition('hna.online_application_id',$online_application_id,'=');
		$result = $query->execute();
		$estate_data = array();
		if($result->rowCount() > 0){
			$data = $result->fetchObject();
			if($data->choice1 != NULL){
				$estate_data[$data->choice1] = $data->choice1_estate_name;
			}if($data->choice2 != NULL){
				$estate_data[$data->choice2] = $data->choice2_estate_name;
			}if($data->choice3 != NULL){
				$estate_data[$data->choice3] = $data->choice3_estate_name;
			}if($data->choice4 != NULL){
				$estate_data[$data->choice4] = $data->choice4_estate_name;
			}
		}
		return $estate_data;
	}
	
	function allot_virtual_RHE(&$estate_list = NULL, $estate_choice_list = NULL){
		$flat_arr = NULL;
		foreach($estate_choice_list as $key => $val){
			if(isset($estate_list[$key])){
				$flat_arr = allot_virtual_RHE_flat($estate_list,$key);
				break;
			}
		}
		if($flat_arr == NULL && count($estate_list) > 0){
			$flat_arr = allot_virtual_RHE_flat($estate_list,current(array_keys($estate_list)));
		}
		return $flat_arr;
	}
	
	function allot_virtual_RHE_flat(&$estate_list = NULL, $key){
		$arr = $estate_list[$key][current(array_keys($estate_list[$key]))];
		$k = current(array_keys($estate_list[$key][current(array_keys($estate_list[$key]))]));
		$flat_arr = array('estate_name' => current(array_keys($estate_list[$key])),'flat_id' => $k, 'flat_no' => $arr[$k]);
		unset($estate_list[$key][current(array_keys($estate_list[$key]))][$k]);
		if(count($estate_list[$key][current(array_keys($estate_list[$key]))]) == 0){
			unset($estate_list[$key]);
		}
		return $flat_arr;
	}
	
	function fetch_roaster_counter(&$virtual_roaster_array = NULL, $desired_catgory = ''){
	/*	echo '<pre>';
		print_r($virtual_roaster_array);
		die();*/
		if(isset($virtual_roaster_array[$desired_catgory])){
			$obj = $virtual_roaster_array[$desired_catgory][current(array_keys($virtual_roaster_array[$desired_catgory]))];
			
			unset($virtual_roaster_array[$desired_catgory][current(array_keys($virtual_roaster_array[$desired_catgory]))]);
			if(count($virtual_roaster_array[$desired_catgory]) == 0){
				unset($virtual_roaster_array[$desired_catgory]);
			}
			
			return $obj;
		}else
			return NULL;
		
	}
	



 