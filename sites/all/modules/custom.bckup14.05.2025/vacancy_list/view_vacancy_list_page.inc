<?php

function vacancy_list_page($flat_type_id = 0, $flat_category_id = 0) {
	
	$flat_status_id = fetch_flat_status_id('vacant');
	$result1 = rhe_flat_status($flat_status_id);
	$data1 = $result1->fetchObject();
	 
	$output = array();
	$result = rhe_flat_allotment_list($flat_type_id, $flat_status_id, $flat_category_id);
	$rows =array();
	$header = array();
	$header['district_name'] = array('data' => 'District');
	$header['estate_name'] = array('data' => 'Name of the RHE');
	$header['estate_address'] = array('data' => 'Estate Address');
	$header['no_of_vacant_flat'] = array('data' => 'No of vacant Flat');
	//$header['flat_list'] = array('data' => 'Flat List');
	$header['flat_status'] = array('data' => 'Flat Status');
	 while($data = $result->fetchObject()) {
		 $fields = array();
		 $fields['district_name'] = $data->district_name;
		 $fields['estate_name'] = $data->estate_name;
		 $fields['estate_address'] = $data->estate_address;
		 $out = rhe_flat_allotment_list_rst_estate($flat_type_id, $flat_status_id, $data->estate_id, $flat_category_id);
		 $fields['no_of_vacant_flat'] = $out[0];
		 //$fields['flat_list'] =$out[1];
		 $fields['flat_status'] = $data1->flat_status;
		 $rows[]  = $fields;
	 }
  
  	$output = theme_table(
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(),
      'sticky' => true,
      'caption' => '',
      'colgroups' => array(),
      'empty' => t("No data found!") // The message to be displayed if table is empty
    )
  ).theme('pager');
  return $output;
	
	
}
