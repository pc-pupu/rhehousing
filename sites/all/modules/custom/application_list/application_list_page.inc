<?php

function application_list_page() {
	global $base_path;
	
	$output = '';
	$result = fetch_application_detail();
	$rows =array();
	$header = array();
	$header[] = array('data' => 'Application Type');
	$header[] = array('data' => 'Application No.');
	$header[] = array('data' => 'Date of Application');
	$header[] = array('data' => 'Status');
	$header[] = array('data' => 'Verification Date');
	$header[] = array('data' => 'View Details');
	//$header[] = array('data' => 'Signed Application Form Upload');

	//$flat_type_id = 0;
	 while($data = $result->fetchObject()) {
		 /*if($flat_type_id != $data->flat_type_id){
			$flat_type_id = $data->flat_type_id;
			$data_arr = fetch_waiting_list($data->flat_type_id);
		 }
		 $data_val = isset($data_arr[$data->online_application_id]) ? $data_arr[$data->online_application_id] : NULL;*/
		 
		 //debolina start
			$current_application_status_description=fetch_application_status_description($data->status);	
			//debolina end


		 $fields = array();
		 $returns = check_application_entity(0,$data->online_application_id);
		 $entityList = $returns[0];
		 $fields[] = 'Application for '.$entityList['type'];
		 if($data->status == 'draft') {
			$fields[] = ''; 
		 } else {
		 	$fields[] = $data->application_no;
		 }
		 $fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));

		 //debolina start
		 // $fields[] = ($data->status == 'allotted') ? 'Allotted Offer' : $data->status;
		  $fields[]=$current_application_status_description;
		 //debolina end


		 $fields[] = implode('/', array_reverse(explode('-', $data->date_of_verified)));
		 if($data->status == 'draft') {
			$fields[] = '';
			$fields[] = '';
		 } else {
		 	$fields[] = l('<img src="'.$base_path.drupal_get_path('module', 'application_list').'/images/view.png" alt="View Icon">', 'view-application/'.encrypt_url($data->online_application_id), array(	  'html'=>TRUE,
		  'attributes'=> array('target' => '_blank'),
		 ));
		 
		 	/* if($data->uploaded_app_form == '') {
		 		$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'application_list').'/images/upload.png" alt="Upload Icon">', 'application_form_upload/'.encrypt_url($data->online_application_id), array('html'=>TRUE));
			} else {
				$download_path = "sites/default/files/";
				$custom_filename = $data->application_no;
				if($data->uri_app_form != '') {
					$path = substr($data->uri_app_form, 9);
					$custom_file_name = $custom_filename.'_Signed_Form';
				}
				$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'application_list').'/images/download.png" alt="Download Icon">', 
				$download_path.$path, array('html'=>TRUE, 'attributes'=> array('download' => $custom_file_name)));
			} */
		 }
		 $rows[] = $fields;
		  
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
  	return $output;
		
}
