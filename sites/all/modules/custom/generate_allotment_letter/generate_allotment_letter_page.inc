<?php

function generate_allotment_letter_page($flat_type_id = 0) {
	$flat_type = fetch_rhe_flat_name_rst_id($flat_type_id);
	
	$output = array();
	$rows =array();
	$header = array();
	$header[] = array('data' => 'Applicant&nbsp;Details&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;');
	$header[] = array('data' => 'Roaster&nbsp;Counter');
	if($flat_type == 'A' || $flat_type == 'B'){
		$header[] = array('data' => 'Grade&nbsp;pay');
	}
	$header[] = array('data' => 'Application&nbsp;Date');
	$header[] = array('data' => 'Flat Type Wise Waiting No');
	$header[] = array('data' => 'Offer');
	$options = array();
	$options['attributes']['style'] = 'color: #0090C7;font-weight: 400;text-decoration: underline;';
	$data_arr = fetch_waiting_list($flat_type_id);
	 foreach($data_arr as $key => $data_val){
		 if(!$data_val['flat_offer']){
			 continue;
		 }
		 $fields = array();
		 $fields[] = $data_val['applicant'];
		 $fields[] = $data_val['roaster_counter'];
		 if($flat_type == 'A' || $flat_type == 'B'){
			 $fields[] = $data_val['grade_pay'];
		 }
		 $fields[] = $data_val['application_date'];
		 $fields[] = $data_val['waiting_no'];
		 $str = $data_val['offer'];
		 $c_arr = array(
			 'flat_id' => $data_val['flat_id'],
			 'online_application_id' => $key, 
			 'flat_type' => $flat_type, 
			 'roaster_counter' => $data_val['rc'],
			 'list_no' => $data_val['ln']
		 );
		 if($data_val['waiting_no'] === '<h6><span>1</span></h6>'){
		 	$str .= '</br>'.l('Generate Allotment Letter' , 'generate_letter/'.json_encode($c_arr),$options);
		 }
		 $fields[] = $str;
		 $rows[] = $fields;
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
