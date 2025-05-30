<?php

	function view_allotment_details_page() {
		global $base_root, $base_path, $user;
		
		$output = '';
		$result = fetch_allotment_details();

		// get document info
		$fetchDoc = get_applicant_upload_docs();
		
		if($fetchDoc->rowCount() >0){
			$doc_arr = $fetchDoc->fetchAllKeyed($key_index = 8, $value_index = 7);
			$license_application_signed_form_url = $base_root.$base_path.'/sites/default/files/doc/'.$user->uid.'/'.$doc_arr['license_application_signed_form'];

			$license_application_signed_form_url = l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png " title="Licence Form" alt="PDF Icon">Uploaded Licence Application Signed Form',$license_application_signed_form_url,array('html'=>true,'attributes'=>array('class'=>array())));

			$declaration_signed_form_url = $base_root.$base_path.'/sites/default/files/doc/'.$user->uid.'/'.$doc_arr['declaration_signed_form'];

			$declaration_signed_form_url = l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png " title="Declaration Form" alt="PDF Icon">Uploaded Declaration Signed Form',$declaration_signed_form_url,array('html'=>true,'attributes'=>array('class'=>array())));

			$current_pay_slip_url = $base_root.$base_path.'/sites/default/files/doc/'.$user->uid.'/'.$doc_arr['current_pay_slip'];

			$current_pay_slip_url = l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png " title="Download Offer Letter" alt="PDF Icon">Uploaded Current Pay Slip',$current_pay_slip_url,array('html' => true));


		}else{
			$license_application_signed_form_url = '';
			$declaration_signed_form_url = '';			
			$current_pay_slip_url = '';
		}
		
		$result1 = fetch_allotment_details();
		$data1 = $result1->fetchObject();
		$rows = array();
		$header = array();
		$header[] = array('data' => 'Allotment No', 'width' => '20%');
		$header[] = array('data' => 'Allotment Date', 'width' => '10%');
		$header[] = array('data' => 'District', 'width' => '15%');
		$header[] = array('data' => 'Flat Type', 'width' => '5%');
		$header[] = array('data' => 'Alloted Estate Name & Address', 'width' => '25%');
		//$header[] = array('data' => 'Alloted Estate Address');
		//$header[] = array('data' => 'Alloted Flat No');
		$header[] = array('data' => 'Status', 'width' => '25%');
		
		while($data = $result->fetchObject()) {
			//$data_val = isset($data_arr[$data->online_application_id]) ? $data_arr[$data->online_application_id] : NULL;
			
			$fields = array();
			$fields[] = $data->allotment_no;
			$fields[] = implode('/', array_reverse(explode('-', $data->allotment_date)));
			$fields[] = $data->district_name;
			$fields[] = $data->flat_type;
			$fields[] =	$data->estate_name.',<br>'.$data->estate_address;
			//$fields[] =	$data->estate_address;
			//$fields[] = $data->flat_no;
			if($data->accept_reject_status == '') {
				$fields[] = '';	
			}
			else if($data->accept_reject_status == 'Accept') {
				$fields[] = 'You '.$data->accept_reject_status.' the Offer of Allotment.';	
			}
			else if($data->accept_reject_status == 'Reject') {
				$fields[] = 'You '.$data->accept_reject_status.' the Offer of Allotment.';	
			}
			else if($data->accept_reject_status == 'Cancel') {
				$fields[] = 'Your Offer of Allotment has been '.$data->accept_reject_status.' because you have not accept Offer of Allotment within one month from the Date of Allotment.';	
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
		
		//
		if($result1->rowCount() > 0) {
			date_default_timezone_set("Asia/Kolkata");
			$current_date = date('Y-m-d'); 
			$allotment_approve_or_reject_date = strtotime($data1->allotment_approve_or_reject_date);
			$final_date = date("Y-m-d", strtotime("+29 days", $allotment_approve_or_reject_date));
			
			if($current_date <= $final_date && $data1->accept_reject_status != 'Cancel') {
				if($data1->accept_reject_status == NULL) {
					$onclick="return confirm('Are you sure you want to accept your allotment?')";
					$onclick1="return confirm('Are you sure you want to reject your allotment?')";
					
					return l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_allotment_details').'/images/accept_icon.png" title="Accept Offer" alt="Accept Icon">Accept Offer', 'status_update/'.encrypt_url($data1->online_application_id).'/'.encrypt_url('Accept'), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'.l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'view_allotment_details').'/images/reject_icon.png" title="Reject Offer" alt="Reject Icon">Reject Offer', 'status_update/'.encrypt_url($data1->online_application_id).'/'.encrypt_url('Reject'), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1, 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).$output;
				}
				else if($data1->accept_reject_status == 'Accept') {
					return l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'view_allotment_details').'/images/pdf_icon.png" title="Download Offer Letter" alt="PDF Icon">Download Offer Letter', 'allotment_detail_pdf_gen/'.encrypt_url($data1->online_application_id).'/'.$data1->allotment_no, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'
					
					<br><br><br>
					'.$license_application_signed_form_url.'
					
					<br><br><br>
					'.$declaration_signed_form_url.'
					
					<br><br><br>
					'.$current_pay_slip_url.$output;
				}
				else if($data1->accept_reject_status == 'Reject') {
					return $output;
				}
			}
			else {
				return $output;
			}
		}
		else {
			return $output;
		}
	}
	
	
	//