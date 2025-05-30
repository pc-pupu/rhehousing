<?php

function allotment_list_hold_page() {
	
	global $base_root, $base_path;
	$output = '';
		$query = db_select('housing_online_application', 'hoa');
		$query->innerJoin('housing_applicant_official_detail', 'haod', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
		$query->innerJoin('housing_applicant', 'ha', 'ha.housing_applicant_id = haod.housing_applicant_id');
		$query->leftJoin('housing_new_allotment_application', 'hnaa', 'hnaa.online_application_id = hoa.online_application_id');
		$query->leftJoin('housing_vs_application', 'hva', 'hva.online_application_id = hoa.online_application_id');
		$query->leftJoin('housing_cs_application', 'hca', 'hca.online_application_id = hoa.online_application_id');
		$query->leftJoin('housing_flat_type', 'hft1', 'hft1.flat_type_id = hnaa.flat_type_id');
		$query->leftJoin('housing_flat_type', 'hft2', 'hft2.flat_type_id = hca.flat_type_id');
		$query->leftJoin('housing_flat_type', 'hft3', 'hft3.flat_type_id = hva.flat_type_id');
		$query->innerjoin('housing_allotment_status_master', 'hasm', 'hasm.short_code = hoa.status');
		$query->innerJoin('housing_flat_occupant', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
		$query->innerJoin('housing_flat', 'hf', 'hf.flat_id = hfo.flat_id');
		$query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query->innerJoin('housing_estate', 'he', 'hf.estate_id = he.estate_id');
		$query->innerJoin('housing_flat_type', 'hft', 'hf.flat_type_id = hft.flat_type_id');
		$query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');
		
		$query->fields('hoa',array('application_no','date_of_application','computer_serial_no','date_of_verified','online_application_id','status'));
		$query->fields('ha',array());
		$query->fields('haod',array());

		$query->addField('hft1', 'flat_type');
		$query->addField('hft2', 'flat_type');
		$query->addField('hft3', 'flat_type');
		$query->addField('hasm', 'status_description');
		$query->addField('hf', 'flat_no');
		$query->addField('hf', 'floor');
		$query->addField('hft', 'flat_type');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$query->addField('hb', 'block_name');
		
		$query->condition('hoa.status','allotment_on_hold','=');
		$query->condition('haod.is_active','1','=');

	


		$result = $query->execute();
		// echo $query;die;
		// $data = $result->fetchAll();
		// echo "<pre>";print_r($data);die;

		///////////////////debaleena 23-09-2024////////////////////////
		$header['sl_no'] = array('data' => 'Name');
		$header['application_no'] = array('data' => 'Application No.');
		$header['date_of_application'] = array('data' => 'Date of Application');
		$header['status'] = array('data' => 'Current Status.');
		$header['flat_no'] = array('data' => 'Flat Alloted');
		$header['floor'] = array('data' => 'Floor');
		$header['flat_type'] = array('data' => 'Flat Type');
		$header['block'] = array('data' => 'Block Name');
		$header['estate_name'] = array('data' => 'Name of R.H.E');
		
	
		$rows =array();
		$output = '';
		
		while($data = $result->fetchObject()) {
			$fields = array();
		
			$fields[] = $data->applicant_name;
			$fields[] = $data->application_no;
			$fields[] = $data->date_of_application;
			$fields[] = $data->status_description;
			$fields[] = $data->flat_no;
			$fields[] = $data->floor;
			if(!empty($data->flat_type)){
				$fields[] = $data->flat_type;
			}else if(!empty($data->hft2_flat_type)){
				$fields[] = $data->hft2_flat_type;
			}else if(!empty($data->hft3_flat_type)){
				$fields[] = $data->hft3_flat_type;
			}
			$fields[] = $data->block_name;
			$fields[] = $data->estate_name;
			
			$rows[] = $fields;
		}

			

			$variables = array(
				'attributes' => array('class'=>array('table table-list table-striped')),
				'header' => $header,
				'rows' => $rows,
				'sticky' => true,
				'empty' => t("No data found!") // The message to be displayed if table is empty
			);
			
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
	
	