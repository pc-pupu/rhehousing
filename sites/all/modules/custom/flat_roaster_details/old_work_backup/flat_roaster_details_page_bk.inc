<?php


	function flat_roaster_details_form($form, &$form_state) {
		$flat_type =  !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : '';

		 $form['flat_type'] = array(
			'#title' => t('Select Flat Type'),
			'#type' => 'select',
			'#options' => rhe_flat_type(),
			'#required' => TRUE,
			'#attributes' => array('class' => array('dropdown1')),
			'#prefix' => '<div >',
			'#suffix' => '</div>',
			'#ajax' => array(
				'event' => 'change',
				//'wrapper' => 'no_of_vacancy',
				'callback' => '_reload_flat_vacancy',
				'method' => 'replace',
			),
		  );
		  
		  
	  $form['vacancy_details'] = array(
		'#prefix' => '<div  id="vacancy_details">',
 		'#suffix' => '</div>',
	  );
	  
	  
	 if($flat_type != '')	 {
		 $vacancy_details = array();
		 $no_of_vacancy = get_no_of_vacancy($flat_type);
		 $vacancy_details = get_vacancy_details($flat_type, $no_of_vacancy);
		 
		 $applicant_details = applicant_details($flat_type, $no_of_vacancy);
		 
		 $output = '';
		 $output .= '<table width="50%">';
		 $output .= '<tr>';
		 $output .= '<td><b>Flat Type</b></td>';
		 $output .= '<td><b>Name of the RHE</b></td>';
		 $output .= '<td><b>Block</b></td>';
		 $output .= '<td><b>Floor</b></td>';
		 $output .= '<td><b>Flat No.</b></td>';
		 $output .= '<td><b>Roaster Counter</b></td>';
		 $output .= '<td><b>Allotment Category</b></td>';
		 $output .= '</tr>';
		 
		 
		 foreach($vacancy_details as $val) {
			  $output .= '<tr>';
			  if($val['allotment_type'] == 5) {
				  $output .= '<td>A+</td>';  
			  }
			  else if($val['allotment_type'] == 1) {
				  $output .= '<td>A</td>';  
			  }
			  else if($val['allotment_type'] == 2) {
				  $output .= '<td>B</td>';  
			  }
			  else if($val['allotment_type'] == 3) {
				  $output .= '<td>C</td>';  
			  }
			  else if($val['allotment_type'] == 4) {
				  $output .= '<td>D</td>';  
			  }
			  $output .= '<td>'.$val['estate_name'].'</td>';
			  $output .= '<td>'.$val['block_name'].'</td>';
			  $output .= '<td>'.$val['floor'].'</td>';
			  $output .= '<td>'.$val['flat_no'].'</td>';
			  $output .= '<td>'.$val['counter'].'</td>';
			  $output .= '<td>'.$val['allotment_category'].'</td>';
			  
			  $output .= '</tr>';
		 }
		 
		 $output .= '</table>';
		 
		 $output .= '<br><br>';
		 
		 $output .= '<table width="50%">';
		 $output .= '<tr>';		 
		 $output .= '<td><b>Flat id</b></td>';
		 $output .= '<td><b>ID</b></td>';
		 $output .= '</tr>';
		 
		 
		 foreach($applicant_details as $val) {
			$output .= '<tr>';
			  $output .= '<td>'.$val['flat_id'].'</td>';
			  $output .= '<td>'.$val['online_application_id'].'</td>';
			  $output .= '</tr>';
		 }
		 
		 
		 $output .= '</table>';
		 
		 
		 
		$form['vacancy_details'] = array(
		'#prefix' => '<div class="two" id="vacancy_details">Vacancy Details : '.$output,
 		'#suffix' => '</div>',
	  );
	}
	
	return $form;
		
		
	}
	
	function flat_roaster_details_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_flat_vacancy(&$form, $form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#vacancy_details", render($form['vacancy_details']));
		return array('#type' => 'ajax', '#commands' => $commands);
  
	}
	
	function get_no_of_vacancy($allotment_type = '') {
		$no_of_vacancy = 0;
		$floor = array('G', 'T');
		$query = db_select('housing_flat', 'hf')
		->fields('hf')
		->condition('flat_type_id', $allotment_type)
		->condition('floor', $floor, 'IN')
		->condition('flat_category_id', 1)
		->condition('flat_status_id', 1);
		$no_of_vacancy = $query->execute()->rowCount();
		
		return $no_of_vacancy;
	
	}
	
	function get_vacancy_details($allotment_type = '', $no_of_vacancy = '') {
		$vacancy_details = array();
		/*$vacancy_details = array(
		
		'allotment_type' => $allotment_type, 'allotment_category' => 'General',
		'allotment_type' => $allotment_type, 'allotment_category' => 'Judicial',
		);*/
		
		
		$result_counter = db_query("select last_roaster_counter from {housing_allotment_roaster_counter} where allotment_type = :allotment_type and id = (select max(id) from {housing_allotment_roaster_counter} where allotment_type = :allotment_type1)", array(':allotment_type' => $allotment_type, ':allotment_type1' => $allotment_type));
		
		if($result_counter->rowCount() > 0) {
			$data_counter = $result_counter->fetchObject();
			$offset_val = $data_counter->last_roaster_counter;
		}
		 else {	
			$offset_val = 0;
		}
		
		
		if($allotment_type == 1 || $allotment_type == 2 || $allotment_type == 5) {
		
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("select * from {housing_roaster4ab_master} order by counter limit :no_of_vacancy offset :offset_val", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
		} 
		else {
			
			$no_from_1st_tab = 29 - $offset_val;
			$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
			$no_of_iteration = 0;
			if($no_of_rest_vacancy % 29 == 0)
				$no_of_iteration = $no_of_rest_vacancy / 29;
			else
				$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
			
			$rest_tab = '';
			for($i=1; $i<= $no_of_iteration; $i++) {
			$rest_tab .= " UNION ALL ";
			$rest_tab .= "(select * from {housing_roaster4ab_master})";
			}
			/*echo "(select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query(" (select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
		
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
		
		
		}
		else if($allotment_type == 3 || $allotment_type == 4) {
		/*	$result = db_query("select * from housing_roaster4cd_master order by counter limit ".$no_of_vacancy." offset ".$offset_val);
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$allotment_category_arr[] = $data->category;
		}
		*/
		
		
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("(select * from {housing_roaster4cd_master} order by counter limit :no_of_vacancy offset :offset_val)", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
		} 
		else {
			
			$no_from_1st_tab = 29 - $offset_val;
			$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
			$no_of_iteration = 0;
			if($no_of_rest_vacancy % 29 == 0)
				$no_of_iteration = $no_of_rest_vacancy / 29;
			else
				$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
			
			$rest_tab = '';
			for($i=1; $i<= $no_of_iteration; $i++) {
			$rest_tab .= " UNION ALL ";
			$rest_tab .= "(select * from {housing_roaster4cd_master})";
			}
			/*echo "(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query("(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
		
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
		
		
		
		
		}
	
		$floor = array('G', 'T');
		$query_for_flat_vacancy = db_select('housing_flat', 'hf');
		$query_for_flat_vacancy->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query_for_flat_vacancy->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query_for_flat_vacancy->fields('hf');
		$query_for_flat_vacancy->fields('he');
		$query_for_flat_vacancy->fields('hb');
		$query_for_flat_vacancy->condition('flat_type_id', $allotment_type);
		$query_for_flat_vacancy->condition('floor', $floor, 'IN');
		$query_for_flat_vacancy->condition('flat_status_id', 1);
		$query_for_flat_vacancy->condition('flat_category_id', 1);
		$query_for_flat_vacancy->orderBy('flat_id', 'ASC');
		$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
		while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
			$flat_vacancy1[] = $data_flat_vacancy->estate_name;
			$flat_vacancy2[] = $data_flat_vacancy->block_name;
			$flat_vacancy3[] = $data_flat_vacancy->floor;
			$flat_vacancy[] = $data_flat_vacancy->flat_no;
			
			$flat_vacancy5[] = $data_flat_vacancy->flat_id;
		}
		
		for($i=0; $i<$no_of_vacancy; $i++) {
			$vacancy_details[] = array(
			'estate_name' => $flat_vacancy1[$i],
			'block_name' => $flat_vacancy2[$i],
			'floor' => $flat_vacancy3[$i],
			'flat_no' => $flat_vacancy[$i],
			'allotment_type' => $allotment_type, 
			'allotment_category' => $allotment_category_arr[$i], 
			'counter' => $roaster_counter_arr[$i],
			
			'flat_id' => $flat_vacancy5[$i],
			);		
		}
		
		return $vacancy_details;
		
		
	}
	
	function applicant_details($allotment_type = '', $no_of_vacancy = '') {
		$allotment_details = array();
		$vacancy_details = get_vacancy_details($allotment_type, $no_of_vacancy);
		
		$temp_id_arr = array();
		$flag = 0;
		for($i=0; $i<sizeof($vacancy_details); $i++) {
			
			
			$flat_id = $vacancy_details[$i]['flat_id'];
			$allotment_type = $vacancy_details[$i]['allotment_type'];
			$allotment_category = $vacancy_details[$i]['allotment_category'];
			$counter = $vacancy_details[$i]['counter'];
			$result = db_query("select hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from {housing_online_application} as hoa 
			inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
			where hoa.status = :status and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category
			order by hoa.online_application_id limit 1", array(':status' => 'verified', ':flat_type_id' => $allotment_type, ':allotment_category' => $allotment_category));
			if($result->rowCount() > 0) {
			$data = $result->fetchObject();
		
			array_push($temp_id_arr, $data->online_application_id);
			
			for($j=0; $j<sizeof($temp_id_arr); $j++) {
			$result1 = db_query("select hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from {housing_online_application} as hoa 
			inner join {housing_new_allotment_application} as hnaa on hnaa.online_application_id = hoa.online_application_id
			where hoa.status = :status and hnaa.flat_type_id = :flat_type_id and hnaa.allotment_category = :allotment_category and hoa.online_application_id != :id
			order by hoa.online_application_id limit 1", array(':status' => 'verified', ':flat_type_id' => $allotment_type, ':allotment_category' => $allotment_category, ':id' => $temp_id_arr[$j]));
		
			if($result1->rowCount() > 0) {	
			
				$flag = 1;
				 
			}
			}
			//$data = $result->fetchObject();
			if($flag == 1) {		
					$allotment_upd_arr[] = array(
					'flat_id' => $flat_id,
					
					'online_application_id' => $data->online_application_id,
					);
			}
			}
		}
		//print_r($temp_id_arr); die();
		
		/*$vacancy_details1 = get_vacancy_details($allotment_type, $no_of_vacancy);
		for($i=0; $i<sizeof($vacancy_details1); $i++) {
			$flat_id = $vacancy_details[$i]['flat_id'];
			
			$floor = array('G', 'T');
			$query_for_flat_vacancy_new = db_select('housing_flat', 'hf')
			->fields('hf')
			->condition('flat_type_id', $allotment_type)
			->condition('floor', $floor, 'IN')
			->condition('flat_status_id', 1)
			->condition('flat_category_id', 1)
			->condition('flat_id', $flat_id, '!=')
			->orderBy('flat_id', 'ASC');
			$no_of_vacancy_new = $query_for_flat_vacancy_new->execute()->rowCount();
			$result_for_flat_vacancy = $query_for_flat_vacancy_new->execute();
			while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
				$flat_vacancy[] = $data_flat_vacancy->flat_id;
			}
		}
		
		for($k=0; $k<$no_of_vacancy_new; $k++) {
			$vacancy_details_new[] = array(
				'flat_id' => $flat_vacancy[$k], 
				'allotment_type' => $allotment_type,
			);		
		}
		
		for($j=0; $j<sizeof($vacancy_details_new); $j++) {
			
			$flat_id = $vacancy_details_new[$j]['flat_id'];
			$allotment_type = $vacancy_details_new[$j]['allotment_type'];
			$result = db_query("select hoa.online_application_id, hnaa.flat_type_id, hnaa.allotment_category from housing_online_application as hoa 
			inner join housing_new_allotment_application as hnaa on hnaa.online_application_id = hoa.online_application_id
			where hoa.status = :status and hnaa.flat_type_id = :flat_type_id 
			and hoa.online_application_id != :application_id
			order by hoa.online_application_id limit 1", array(':status' => 'verified', ':flat_type_id' => $allotment_type, ':application_id' => $allotment_upd_arr[$j]['online_application_id']));
		
			$data = $result->fetchObject();
		
			if($result->rowCount() > 0) {
				
				$allotment_upd_arr[] = array(
					'flat_id' => $flat_id,
					'online_application_id' => $data->online_application_id,
				);
			}
			
		}*/
		
		return $allotment_upd_arr;
		
	}