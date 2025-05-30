<?php

	function housing_list_page($flat_type_id = 0, $flat_category_id = 0) {
		
		$output = '';
		$result = all_housing_list($flat_type_id, $flat_category_id);
		$rows =array();
		$header = array();
		$header['district_name'] = array('data' => 'District');
		$header['estate_name'] = array('data' => 'Name of the RHE');
		$header['estate_address'] = array('data' => 'Estate Address');
		 while($data = $result->fetchObject()) {
			 $fields = array();
			 $fields['district_name'] = $data->district_name;
			 $fields['estate_name'] = $data->estate_name;
			 $fields['estate_address'] = $data->estate_address;
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