<?php

	function generate_cs_licence_page() {
		global $base_path;
		global $user_role;
		
		$output = '';
		$result = cs_allotment_details_fetch();
		
		$result2 = cs_allotment_details_fetch();
		$data2 = $result2->fetchObject();
		
		$rows = array();
		$header = array();
		$header[] = array('data' => 'Allotment No');
		$header[] = array('data' => 'Allotment Date');
		$header[] = array('data' => 'District');
		//$header[] = array('data' => 'Flat Type');
		$header[] = array('data' => 'Alloted Estate Name & Address');
		//$header[] = array('data' => 'Alloted Estate Address');
		//$header[] = array('data' => 'Alloted Flat No');
		if($data2->status == 'verified') {
			$header[] = array('data' => 'Action');
			$header[] = array('data' => 'Signed Licence Upload');
		} else if($data2->status == 'issued') {
			$header[] = array('data' => 'Action');
			$header[] = array('data' => 'Signed Licence Upload');	
		}
		$options = array();
		//$options['attributes']['style'] = 'color: #0090C7;font-weight: 400;text-decoration: underline;';
		while($data = $result->fetchObject()) {
			$result1 = cs_licence_details($data->online_application_id, $data->flat_occupant_id, $data->license_application_id);
			$data1 = $result1->fetchObject();
			
			$fields = array();
			$fields[] = $data->allotment_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->allotment_date)));
			$fields[] = $data->allotment_district;
			//$fields[] = $data->flat_type;
			$fields[] =	$data->allotment_estate.', '.$data->allotment_address;
			//$fields[] =	$data->estate_address;
			//$fields[] = $data->flat_no;
			
			$onclick="return confirm('Are you sure you want to generate licence?')";
			$onclick1="return confirm('Are you sure you want to download licence as PDF?')";
			
			if($data->status == 'verified') {
				if($user_role == 6) {
					$fields[] = l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'generate_cs_licence').'/images/generate_icon.png" title="Generate CS Licence" alt="Generate Licence Icon">Generate CS Licence' , 'update_cs_licence_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url($data->flat_occupant_id).'/'.encrypt_url($data->license_application_id), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: underline; font-size:12px')));
					$fields[] = '';
				} else {
					$fields[] = 'Licence Not Generated.';
					$fields[] = '';	
				}
			}
			else if($data->status == 'issued'){
				
				$fields[] = l('<img height="16" width="16" src="'.$base_path.drupal_get_path('module', 'generate_cs_licence').'/images/pdf_icon.png" title="Download CS Licence" alt="PDF Icon">Download CS Licence' , 'cs_licence_pdf_gen/'.encrypt_url($data->online_application_id).'/'.encrypt_url($data->flat_occupant_id).'/'.encrypt_url($data->license_application_id).'/cs_licence_'.$data1->license_no, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:12px')));
				
				if($data1->uploaded_licence == '') {
					$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'generate_cs_licence').'/images/upload.png" alt="Upload Icon">', 'signed_cs_licence_upload/'.encrypt_url($data1->occupant_license_id).'/'.encrypt_url($data1->license_no), array('html'=>TRUE));
				} else if($data1->uploaded_licence != '') {
					$download_path = "sites/default/files/";
					$custom_filename = $data1->license_no;
					if($data1->uri_signed_licence != '') {
						$path = substr($data1->uri_signed_licence, 9);
						$custom_file_name = $custom_filename.'_Signed_Category_Shifting_Licence';
					}
					$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'generate_cs_licence').'/images/download.png" alt="Download Icon">', $download_path.$path, array('html'=>TRUE, 'attributes'=> array('download' => $custom_file_name)));	
				}
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