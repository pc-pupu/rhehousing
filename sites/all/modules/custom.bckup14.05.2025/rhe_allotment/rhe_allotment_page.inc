<?php
function rhe_allotment_form($form, $form_state) {	
	$allotment_type =  !empty($form_state['values']['allotment_type']) ? $form_state['values']['allotment_type'] : '';
	if(isset($form_state['values']['show_vacancy'])) {
		$report_content = get_vacancy_applicant($allotment_type, $form_state['values']['district_code']);
	} else {
		$report_content = '';
	}
	
	$form['allotment_type'] = array(
		'#title' => t('Select Allotment Type'),
		'#type' => 'select',
		'#options' => rhe_flat_type(),
		'#required' => TRUE,
		'#attributes' => array('class' => array('form-select')),//sd 24-06-2024
		'#prefix' => '<div class="col-md-6"><div class="form-floating">',//sd 24-06-2024
		'#suffix' => '</div></div>',//sd 24-06-2024
	);  

	$form['district_code'] = array(
		'#type' => 'hidden',
		'#value' => 17
	);
	  
	$form['show_vacancy'] = array(
		'#type' => 'submit',
		'#value' => 'Show vacancy',
		'#attributes' => array('class'=>array('btn bg-primary btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),//sd 24-06-2024;
		'#prefix' => '<div class="row"><div class="col-md-6" >',//sd 24-06-2024;
		'#suffix' => '</div>',//sd 24-06-2024;
	);

	if($report_content != '') {
		$form['allotment'] = array(
			'#type' => 'submit',
			'#value' => 'Allot flat',
			'#attributes' => array('class'=>array('btn bg-danger btn-sm px-5 rounded-pill text-white mb-4 fw-bolder')),//sd 24-06-2024;
			'#prefix' => '<div class="col-md-6">',//sd 24-06-2024;
			'#suffix' => '</div></div>',//sd 24-06-2024;
		);
	}

	$form['divToPrint'] = array(
		'#prefix' => '<div class="printable"><div id="divToPrint" style="width:100% !important;">' . $report_content,
		'#suffix' => '</div></div>',
	);
			
	return $form;
}

function rhe_allotment_form_submit($form, &$form_state) {
	$op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
	if($op == 'Allot flat') {
		module_load_include('inc', 'rhe_allotment', 'rhe_allotment_update');
		$allotment_type = $form_state['values']['allotment_type'];
		$district_code = $form_state['values']['district_code'];
		$get_applicant_count = get_applicant_total_count($allotment_type);   //added by debaleena 24.07.2024
		//echo $get_applicant_count;die;
		if($get_applicant_count > 0) //added by debaleena 24.07.2024
		{
			rhe_allotment_update($allotment_type, $district_code);
			drupal_set_message('Allotment Process Completed Successfully');
		}else{
			drupal_set_message('No Application Available for Allotment','error');
		}
		

		
	}
	$form_state['rebuild'] = TRUE;
}

function get_vacancy_applicant($allotment_type, $district_code = 0) {
	global $base_url;

	$allvacancy = "";
	$allvacancy = get_estatewise_vacancy($allotment_type, $district_code );

	$report_table = '<table class="allotment table table-list">
		<tr>
			<th rowspan="2">Housing</th>
			<th colspan="10">No. of Vacancy</th>
			<th colspan="3">No. of Applicant</th>
		</tr>
		<tr>
			<th>Floor-0</th>
			<th>Floor-1</th>
			<th>Floor-2</th>
			<th>Floor-3</th>
			<th>Floor-4</th>
			<th>Floor-5</th>
			<th>Floor-6</th>
			<th>Floor-7</th>
			<th>Floor-8</th>
			<th>Floor-Top</th>
			<th>Floor shifting</th>
			<th>Category shifting</th>
			<th>New/ Fresh</th>
		</tr>';
		
		if($allvacancy -> rowCount() > 0) {
			$total_record = $allvacancy -> rowCount();
			$counter = 1; $applicant_new = 0; $rowspan = 0;
			foreach($allvacancy as $record) { 
				$applicant_vs = get_no_of_applicant_vs($allotment_type, $record->estate_id);
				$applicant_cs = get_no_of_applicant_cs($allotment_type, $record->estate_id);
				if($counter == 1) {
					
					$applicant_new = get_no_of_applicant_new($allotment_type);
					$rowspan = $total_record;
				}
				//echo $rowspan;die;
				
				$applicant_total = $applicant_vs + $applicant_cs + $applicant_new;				
				// echo $applicant_total;die;
				if($counter == 1) {
					$report_table .= '<tr>
						<td>' . $record -> estate_name . '</td>
						<td>' . $record -> floor_0 . '</td>
						<td>' . $record -> floor_1 . '</td>
						<td>' . $record -> floor_2 . '</td>
						<td>' . $record -> floor_3 . '</td>
						<td>' . $record -> floor_4 . '</td>
						<td>' . $record -> floor_5 . '</td>
						<td>' . $record -> floor_6 . '</td>
						<td>' . $record -> floor_7 . '</td>
						<td>' . $record -> floor_8 . '</td>
						
						<td>' . $record -> floor_top . '</td>
						<td>' . $applicant_vs . '</td>
						<td>' . $applicant_cs . '</td>
						<td rowspan = "' . $rowspan . '">' . $applicant_new . '</td>
					</tr>';
				} else {
					$report_table .= '<tr>
						<td>' . $record -> estate_name . '</td>
						<td>' . $record -> floor_0 . '</td>
						<td>' . $record -> floor_1 . '</td>
						<td>' . $record -> floor_2 . '</td>
						<td>' . $record -> floor_3 . '</td>
						<td>' . $record -> floor_4 . '</td>
						<td>' . $record -> floor_5 . '</td>
						<td>' . $record -> floor_6 . '</td>
						<td>' . $record -> floor_7 . '</td>
						<td>' . $record -> floor_8 . '</td>
						
						<td>' . $record -> floor_top . '</td>
						<td>' . $applicant_vs . '</td>
						<td>' . $applicant_cs . '</td>
						
					</tr>';
				}	
				$counter++;			
			}
		}

		$report_table .= '</table>';

	return $report_table;

}