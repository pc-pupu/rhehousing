<?php


	function flat_roaster_details_form($form, &$form_state) {
		$flat_type =  isset($form_state['values']['flat_type']) && !empty($form_state['values']['flat_type']) ? $form_state['values']['flat_type'] : '';

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
		  
		$form['vacancy_details'] = array(
		'#type' => 'markup',
		'#markup' => viewFlatRoasterList($flat_type),
		'#prefix' => '<div id="vacancy_details">',
 		'#suffix' => '</div>',
	  );
	}
	
	return $form;
		
		
	}
	
	function flat_roaster_details_form_submit($form, &$form_state) {
		$form_state['rebuild'] = TRUE;
	}
	
	function _reload_flat_vacancy($form, &$form_state) {
		$commands = array();
		$commands[] = ajax_command_replace("#vacancy_details", drupal_render($form['vacancy_details']));
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
	
	function viewFlatRoasterList($flat_type = '') {
		 global $base_path;
		 
		 $vacancy_details = array();
		 $no_of_vacancy = get_no_of_vacancy($flat_type);
		 $vacancy_details = get_vacancy_details($flat_type, $no_of_vacancy);
		 
		 $output = '';
		 
		 $header = array();
		 $rows =array();
		 $header[] = array('data' => 'Flat Type');
		 $header[] = array('data' => 'Name of the RHE');
		 $header[] = array('data' => 'Block');
		 $header[] = array('data' => 'Floor');
		 $header[] = array('data' => 'Flat No.');
		 $header[] = array('data' => 'Roaster Counter');
		 $header[] = array('data' => 'Allotment Category');
		 
		 foreach($vacancy_details as $val) {
			  $fields = array();
			  if($val['allotment_type'] == 5) {
				  $fields[] = 'A+';  
			  }
			  else if($val['allotment_type'] == 1) {
				  $fields[] = 'A';  
			  }
			  else if($val['allotment_type'] == 2) {
				  $fields[] = 'B';  
			  }
			  else if($val['allotment_type'] == 3) {
				  $fields[] = 'C';  
			  }
			  else if($val['allotment_type'] == 4) {
				  $fields[] = 'D';  
			  }
			  $fields[] = $val['estate_name'];
			  $fields[] = $val['block_name'];
			  $fields[] = $val['floor'];
			  $fields[] = $val['flat_no'];
			  $fields[] = $val['counter'];
			  $fields[] = $val['allotment_category'];
			  
			   $rows[]  = $fields;
		 }
		 
		 /*$output = theme_table(
			array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array(),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
		).theme('pager');*/
		
		if(count($rows) > 0) {
		// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array(),
			);
	 
			// Or, render using a theme function.
			$variables = array(
			  'attributes' => array(),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
						<table class="datatable_no_data_found">
							<tr class="tr_no_data_found">
								<th class="th_no_data_found"></th>
							</tr>
							<tr class="tr_no_data_found">
								<td class="td_no_data_found">No data found!</td>
							</tr>
						</table>
					</div>';	
		}
		
		if(count($rows) > 0) {
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'flat_roaster_details').'/images/pdf_icon.png" title="Download Flat Roaster Details" alt="PDF Icon">Download Flat Roaster Details', 'flat_roaster_details_pdf/'.encrypt_url($flat_type).'/'.encrypt_url($no_of_vacancy).'/flat_roaster_details_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
		}
		else {
			return $output;
		}
		
		
		
		
	}