<?php

function vacancy_list_page($district_id = 0, $flat_type_id = 0) {
	global $base_path;
	
	$flat_status_id = fetch_flat_status_id('vacant');
	$result1 = rhe_flat_status($flat_status_id);
	$data1 = $result1->fetchObject();
	 
	$output = array();
	$result = rhe_flat_allotment_list($district_id, $flat_type_id, $flat_status_id);
	
	$result2 = rhe_flat_allotment_list($district_id, $flat_type_id, $flat_status_id);
	$data2 = $result2->fetchObject();
	
	//$rows = array();//sd turned off 21-06-2024
	//$header = array();//sd turned off 21-06-2024
	$header['slno'] = array('data' => 'Sl. No.', 'width' => '5%');
	$header['district_name'] = array('data' => 'District', 'width' => '14%');
	$header['estate_name'] = array('data' => 'Name of the RHE', 'width' => '23%');
	$header['estate_address'] = array('data' => 'Estate Address', 'width' => '23%');
	$header['flat_list'] = array('data' => 'Flat No.', 'width' => '20%');
	$header['no_of_vacant_flat'] = array('data' => 'No of vacant Flat', 'width' => '15%');
	//$header['flat_status'] = array('data' => 'Flat Status');
	
	$i = 1;
	 while($data = $result->fetchObject()) {
		 $fields = array();
		 $fields['slno'] = $i;
		 $fields['district_name'] = $data->district_name;
		 $fields['estate_name'] = $data->estate_name;
		 $fields['estate_address'] = $data->estate_address;
		 $out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data->estate_id);
		 $fields['flat_list'] = $out[1];
		 $fields['no_of_vacant_flat'] = $out[0];
		 //$fields['flat_status'] = $data1->flat_status;
		 
		 $i++;
		 $rows[] = $fields;
		 
		 $total_no_flat = $total_no_flat + $out[0];
	 }
	 
	 /*$fields1 = array();
	 $fields1['total flat'] = t('Total No. of Vacant Flat');
	 $fields1['total_no_flat'] = $total_no_flat;
  	 $rows[] = $fields1;*/
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
	
	// sd 21-06-2024 start
	$variables = array(
		'attributes' => array('class'=>array('table table-list table-striped')),
		'header' => $header,
		'rows' => $rows,
		'sticky' => true,
		'empty' => t("No data found!") // The message to be displayed if table is empty
	  );
		
	
	$output = theme('datatable', $variables);
	//end
	
	//sd turned off 21-06-2024
	/*if($result->rowCount() > 0) {
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
	}*/
  
  
	if($result->rowCount() > 0) {
		//sd turned off 21-06-2024
		//return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'vacancy_list').'/images/pdf_icon.png" title="Download Flat Vacancy List" alt="PDF Icon">Download Flat Vacancy List', 'flat_vacancy_list_pdf/'.encrypt_url($district_id).'/'.encrypt_url($flat_type_id).'/'.encrypt_url($flat_status_id).'/'.$data2->flat_type.'_type_flat_vacancy_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
		return l('Download Flat Vacancy List','flat_vacancy_list_pdf/'.encrypt_url($district_id).'/'.encrypt_url($flat_type_id).'/'.encrypt_url($flat_status_id).'/'.$data2->flat_type.'_type_flat_vacancy_list_'.time(),array('html'=>TRUE,'attributes' => array('target' => '_blank','class' => 'btn bg-primary  px-5 rounded-pill text-white fw-bolder mb-2'))).'<div class="mb-5 pb-3">'.$output.'</div>';//sd 21-06-2024
	}
	/*else {//sd turned off 21-06-2024
		return $output;
	}*/
}
