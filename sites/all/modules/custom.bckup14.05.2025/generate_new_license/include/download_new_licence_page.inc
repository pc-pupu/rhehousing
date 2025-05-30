<?php

	function download_new_licence_page() {
		global $base_path;
		global $user;
		
		$output = '';
		$result = allotment_details_fetch($user->uid);
		
		$rows = array();
		$header = array();
		
		/*$header[] = array('data' => 'Licence No.');
		$header[] = array('data' => 'Licence Issue Date');
		$header[] = array('data' => 'Licence Expiry Date');*/
		$header[] = array('data' => 'Status');
		
		while($data = $result->fetchObject()) {
			$result1 = licence_details($data->online_application_id, $data->flat_occupant_id, $data->license_application_id);
			$data1 = $result1->fetchObject();
			
			$fields = array();
			
			$onclick = "return confirm('Are you sure you want to download licence as PDF?')";
			
			if($data->status == 'verified') {
				$fields[] = 'Your Licence has not yet generated.';
			}
			else if($data->status == 'issued' && $data1->uploaded_licence == ''){
				$fields[] = 'Your Licence has not yet signed and uploaded.';	
			}
			else if($data->status == 'issued' && $data1->uploaded_licence != ''){
				
				/*$fields[] = $data->license_no;
				$fields[] = implode('/', array_reverse(explode('-', $data->license_issue_date)));
				$fields[] = implode('/', array_reverse(explode('-', $data->license_expiry_date)));*/
				
				/*$fields[] = l('<img height="16" width="16" src="'.$base_path.drupal_get_path('module', 'generate_new_license').'/images/pdf_icon.png" title="Download Licence" alt="PDF Icon">Download Licence' , 'license_pdf_gen/'.encrypt_url($data->online_application_id).'/'.encrypt_url($data->flat_occupant_id).'/'.encrypt_url($data->license_application_id).'/new_licence_'.$data1->license_no, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:12px')));*/
				
				
				$download_path = "sites/default/files/";
				$custom_filename = $data1->license_no;
				if($data1->uri_signed_licence != '') {
					$path = substr($data1->uri_signed_licence, 9);
					$custom_file_name = $custom_filename.'_Signed_New_Licence';
				}
				$fields[] = l('<img width="40" height="40" src="'.$base_path.drupal_get_path('module', 'generate_new_license').'/images/download.png" alt="Download Icon">Download Licence', $download_path.$path, array('html'=>TRUE, 'attributes'=> array('download' => $custom_file_name, 'style' => 'color: #0090C7; font-size:18px')));
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