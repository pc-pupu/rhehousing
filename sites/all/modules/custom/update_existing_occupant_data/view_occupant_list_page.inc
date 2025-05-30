<?php

function viewOccupantList() {
	global $base_path;
	 
	$output = '';
	$result = rhe_occupant_list();
	$rows =array();
	$header = array();
	$header[] = array('data' => 'Applicant Name');
	$header[] = array('data' => 'User Type');
	$header[] = array('data' => 'Mobile No');
	$header[] = array('data' => 'RHE Flat No');
	$header[] = array('data' => 'RHE Name');
	$header[] = array('data' => 'Flat Type');
	$header[] = array('data' => 'Allotment No');
	$header[] = array('data' => 'Licence No');
	$header[] = array('data' => 'View Detail');

	 while($data = $result->fetchObject()) {
		 $fields = array();
		 $fields[] = $data->applicant_name;
		 $fields[] = 'Offline User';
		 $fields[] = $data->mobile_no;
		 $fields[] = $data->flat_no;
		 $fields[] = $data->estate_name;
		 $fields[] = $data->flat_type;
		 $fields[] = $data->allotment_no;
		 $fields[] = $data->license_no;
		 
		 
		 $src=$base_path.drupal_get_path('module', 'update_existing_occupant_data').'/images/view1.png';
		 $fields[] = l(
		 				'<img src="'.$src.'" alt="View Icon">',
		 				'update_occupant/view/'.encrypt_url($data->existing_flat_occupant_id),
						array(
								'html'=>TRUE,
								//'attributes'=> array('target' => '_blank'),
							)
					);																																				
		 $rows[]  = $fields;
	 }
	 $result = rhe_eoccupant_list();
	 while($data = $result->fetchObject()) {
		 $fields = array();
		 $fields[] = $data->applicant_name;
		 $fields[] = 'e-User';
		 $fields[] = $data->mobile_no;
		 $fields[] = $data->flat_no;
		 $fields[] = $data->estate_name;
		 $fields[] = $data->flat_type;
		 $fields[] = $data->allotment_no;
		 $fields[] = $data->license_no;
		 
		 
		 $src1=$base_path.drupal_get_path('module', 'update_existing_occupant_data').'/images/view1.png';
		 $fields[] = l(
		 				'<img src="'.$src1.'">',
						'update_occupant/view/'.encrypt_url($data->online_application_id),
						array(
								'html'=>TRUE,
			  					//'attributes'=> array('target' => '_blank'),
			 			)
					);
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
