<?php
/*Done by Subham*/
	function rhewise_occupant_draft_list() {  
		
		global $base_root, $base_path,$user;
		$output = '';

			$query_dtls = db_select('users_details', 'ud'); 
			$query_dtls->fields('ud');
			$query_dtls->condition('uid',$user->uid,'=');
			$rsult = $query_dtls->execute();
			$data_fetch = $rsult->fetchObject();

			if($data_fetch->division_id != '' && $data_fetch->subdiv_id != '') { 
				if($data_fetch->subdiv_id != 0) {								
					$query = db_select('housing_existing_occupant_draft', 'heod');
                    
                    $query->innerJoin('housing_flat', 'hf', 'hf.flat_id = heod.flat_id');
                    $query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
                    $query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
                    $query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');

					$query->addField('heod', 'applicant_name');
					$query->fields('he', array('estate_name', 'estate_address'));
					$query->addField('hft', 'flat_type');
					$query->fields('hf', array('floor', 'flat_no'));
                    $query->addField('hd', 'district_name');
                    $query->addField('hb', 'block_name');
					$query->addField('heod', 'housing_existing_occupant_draft_id');

                    $db_and = db_and();							
					$db_and->condition('he.division_id', $data_fetch->division_id, '=');	
					$db_and->condition('he.subdiv_id', $data_fetch->subdiv_id, '=');		
					$query->condition($db_and);

					$result =$query->execute();

				} else{																		
					$query = db_select('housing_existing_occupant_draft', 'heod');
                    
                    $query->innerJoin('housing_flat', 'hf', 'hf.flat_id = heod.flat_id');
                    $query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
					$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
                    $query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');

					$query->addField('heod', 'applicant_name');
					$query->fields('he', array('estate_name', 'estate_address'));
					$query->addField('hft', 'flat_type');
					$query->fields('hf', array('floor', 'flat_no'));
                    $query->addField('hd', 'district_name');
					$query->addField('heod', 'housing_existing_occupant_draft_id');

					$query->condition('he.division_id', $data_fetch->division_id, '=');
					$result =$query->execute();
				}
			}
			

			$header['Serial No.'] = array('data' => 'Serial No.');
			$header['Applicant Name'] = array('data' => 'Applicant Name');
            $header['District'] = array('data' => 'District');
			$header['Estate Name'] = array('data' => 'Estate Name');
			$header['Flat Type'] = array('data' => 'Flat Type');
			$header['Flat No.'] = array('data' => 'Flat No.');
			$header['Floor'] = array('data' => 'Floor');
			$header['Details'] = array('data' => 'Details');
           

			$rows =array();
			$output = '';
			$serialNumber = 1;
		
		while($data = $result->fetchObject()) {
            // print_r($data);die;
			$fields = array();
      
			$fields[] = $serialNumber;
			$fields[] = $data->applicant_name;
            $fields[] = $data->district_name;
			$fields[] = $data->estate_name;
			$fields[] = $data->flat_type;
			$fields[] = $data->flat_no;
			$fields[] = $data->floor;
			// if($data->status == 0){
			// 	$fields[] = 'Pending Approval at Division Level';
			// }else{
			// 	$fields[] = 'Approved by Division';
			// }
			$fields[] = l(
            'View Details',
            'existing-occupant-view-det-draft/'. encrypt_url($data->housing_existing_occupant_draft_id),
            array(
                'html'=>TRUE,
                'attributes'=> array('class'=>array('btn bg-success btn-sm px-4 rounded-pill text-white fw-bolder')),
            ));	
			$serialNumber++;

			$rows[] = $fields;
			
		}

		$variables = array(
			'attributes' => array('class'=>array('table table-list table-striped')),
			'header' => $header,
			'rows' => $rows,
			'sticky' => true,
			'empty' => t("No data found!")
		  );
  		//end

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
			  'attributes' => array('class'=>array('table table-list table-striped')),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
							<table class="datatable_no_data_found table table-list">
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