<?php

function vacancy_list_page($flat_type_id = 0, $flat_category_id = 0) {
	global $base_path;
	
	$flat_status_id = fetch_flat_status_id('vacant');
	$result1 = rhe_flat_status($flat_status_id);
	$data1 = $result1->fetchObject();
	 
	$output = array();
	$result = rhe_flat_allotment_list($flat_type_id, $flat_status_id, $flat_category_id);
	$rows =array();
	$header = array();
	$header['slno'] = array('data' => 'Sl. No.');
	$header['district_name'] = array('data' => 'District');
	$header['estate_name'] = array('data' => 'Name of the RHE');
	$header['estate_address'] = array('data' => 'Estate Address');
	$header['flat_list'] = array('data' => 'Flat No.');
	$header['no_of_vacant_flat'] = array('data' => 'No of vacant Flat');
	//$header['flat_status'] = array('data' => 'Flat Status');
	
	$i = 1;
	 while($data = $result->fetchObject()) {
		 $fields = array();
		 $fields['slno'] = $i;
		 $fields['district_name'] = $data->district_name;
		 $fields['estate_name'] = $data->estate_name;
		 $fields['estate_address'] = $data->estate_address;
		 $out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data->estate_id, $flat_category_id);
		 $fields['flat_list'] =$out[1];
		 $fields['no_of_vacant_flat'] = $out[0];
		 //$fields['flat_status'] = $data1->flat_status;
		 
		 $i ++;
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
	
	if($result->rowCount() > 0) {
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
  
  
	if($result->rowCount() > 0) {
			return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'vacancy_list').'/images/pdf_icon.png" title="Download Flat Vacancy List" alt="PDF Icon">Download Flat Vacancy List', 'flat_vacancy_list_pdf/'.encrypt_url($flat_type_id).'/'.encrypt_url($flat_category_id).'/'.encrypt_url($flat_status_id).'/flat_vacancy_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
	}
	else {
		return $output;
	}
}
