<?php

function generate_allotment_letter_page($flat_type_id = 0) {
	
	$output = array();
	$rows =array();
	$header = array();
	$header[] = array('data' => 'Applicant&nbsp;Name');
	$header[] = array('data' => 'Application&nbsp;Type');
	$header[] = array('data' => 'Roaster&nbsp;Counter');
	$header[] = array('data' => 'Offer');
	$header[] = array('data' => 'Action');
	$result = fetch_allotment_letter_list($flat_type_id);
	$i = 0;
	 while($data = $result->fetchObject()){
		 $fields = array();
		 $allotment_category = '';
		 $application_type = '';
		 if($data->n_allotment_category != NULL){
			 $allotment_category = $data->n_allotment_category;
			 $application_type = 'New&nbsp;Allotment';
		 }else if($data->v_allotment_category != NULL){
			 $allotment_category = $data->v_allotment_category;
			 $application_type = 'Vertical&nbsp;Shifting'; 
		 }else if($data->c_allotment_category != NULL){
			 $allotment_category = $data->c_allotment_category;
			 $application_type = 'Category&nbsp;Shifting';
		 }
		 $fields[] = '<h6><label style="color:#2F709B;letter-spacing: 0.06em;">'.str_replace(' ','&nbsp;',$data->applicant_name).'</label><label style="color:#0090C7;font-weight: 400;display:block;">('.str_replace(' ','&nbsp;',$allotment_category).')</label></h6>';	
		 $fields[] = '<h6><label style="color:#0090C7;font-weight: 400;">'.$application_type.'</label></h6>';
		 $fields[] = '<h6><label style="color:#596C26;display: block;font-weight: 500;">'.$data->roaster_counter.' / List '.$data->list_no.'</label></h6>';	
		 $fields[] = '<h6><label >Flat:&nbsp;'.$data->flat_no.'&nbsp;<label style="color:#0090C7;font-weight: 400;">[&nbsp;'.str_replace(' ','&nbsp;',$data->estate_name).'&nbsp;]</label></label></h6>';	 
		 if($i++ == 0){
			 $onclick="return confirm('Are you sure you want to Allot?')";
			 $onclick1="return confirm('Are you sure you want to Cancel?')";
			 
		 	$fields[] = l('Allot&nbsp;&nbsp;', 'update_allotment/'.encrypt_url($data->online_application_id).'/'.encrypt_url('allot'),array('html'=>TRUE, 'attributes' => array('onclick' => $onclick))).'&nbsp;|&nbsp;'.l('&nbsp;&nbsp;Cancel', 'update_allotment/'.encrypt_url($data->online_application_id).'/'.encrypt_url('cancel'),array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1)));
		 }else{
			 $fields[] = '';
		 }
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
