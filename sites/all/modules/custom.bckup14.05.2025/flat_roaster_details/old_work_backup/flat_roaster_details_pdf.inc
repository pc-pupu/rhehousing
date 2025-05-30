<?php
	
	function get_vacancy_details($allotment_type = '', $no_of_vacancy = '') {
		$vacancy_details = array();
		/*$vacancy_details = array(
		
		'allotment_type' => $allotment_type, 'allotment_category' => 'General',
		'allotment_type' => $allotment_type, 'allotment_category' => 'Judicial',
		);*/
		
		
		$result_counter = db_query("select last_roaster_counter from {housing_allotment_roaster_counter} where allotment_type = :allotment_type and id = (select max(id) from {housing_allotment_roaster_counter} where allotment_type = :allotment_type1)", array(':allotment_type' => $allotment_type, ':allotment_type1' => $allotment_type));
		
		if($result_counter->rowCount() > 0) {
		$data_counter = $result_counter->fetchObject();
		$offset_val = $data_counter->last_roaster_counter;
		} else {	
		$offset_val = 0;
		}
		
		
		if($allotment_type == 1 || $allotment_type == 2 || $allotment_type == 5) {
		
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("select * from {housing_roaster4ab_master} order by counter limit :no_of_vacancy offset :offset_val", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
		} 
		else {
			
			$no_from_1st_tab = 29 - $offset_val;
			$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
			$no_of_iteration = 0;
			if($no_of_rest_vacancy % 29 == 0)
				$no_of_iteration = $no_of_rest_vacancy / 29;
			else
				$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
			
			$rest_tab = '';
			for($i=1; $i<= $no_of_iteration; $i++) {
			$rest_tab .= " UNION ALL ";
			$rest_tab .= "(select * from {housing_roaster4ab_master})";
			}
			/*echo "(select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query(" (select * from housing_roaster4ab_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
		
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
		
		
		}
		else if($allotment_type == 3 || $allotment_type == 4) {
		/*	$result = db_query("select * from housing_roaster4cd_master order by counter limit ".$no_of_vacancy." offset ".$offset_val);
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$allotment_category_arr[] = $data->category;
		}
		*/
		
		
		if(29 - $offset_val >= $no_of_vacancy) {
			$result = db_query("(select * from {housing_roaster4cd_master} order by counter limit :no_of_vacancy offset :offset_val)", array(':no_of_vacancy' => $no_of_vacancy, ':offset_val' => $offset_val)); 
		} 
		else {
			
			$no_from_1st_tab = 29 - $offset_val;
			$no_of_rest_vacancy = $no_of_vacancy - $no_from_1st_tab;
			$no_of_iteration = 0;
			if($no_of_rest_vacancy % 29 == 0)
				$no_of_iteration = $no_of_rest_vacancy / 29;
			else
				$no_of_iteration = ($no_of_rest_vacancy / 29) + 1;
			
			$rest_tab = '';
			for($i=1; $i<= $no_of_iteration; $i++) {
			$rest_tab .= " UNION ALL ";
			$rest_tab .= "(select * from {housing_roaster4cd_master})";
			}
			/*echo "(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab;*/
			$result = db_query("(select * from housing_roaster4cd_master order by counter limit ".$no_from_1st_tab." offset ".$offset_val.") ".$rest_tab);
			
		}
		
		$allotment_category_arr = array();
		while($data = $result->fetchObject()){
			$roaster_counter_arr[] = $data->counter;
			$allotment_category_arr[] = $data->category;
		}
		
		
		
		
		}
	
		$floor = array('G', 'T');
		$query_for_flat_vacancy = db_select('housing_flat', 'hf');
		$query_for_flat_vacancy->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query_for_flat_vacancy->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query_for_flat_vacancy->fields('hf');
		$query_for_flat_vacancy->fields('he');
		$query_for_flat_vacancy->fields('hb');
		$query_for_flat_vacancy->condition('flat_type_id', $allotment_type);
		$query_for_flat_vacancy->condition('floor', $floor, 'IN');
		$query_for_flat_vacancy->condition('flat_status_id', 1);
		$query_for_flat_vacancy->condition('flat_category_id', 1);
		$query_for_flat_vacancy->orderBy('flat_id', 'ASC');
		$result_for_flat_vacancy = $query_for_flat_vacancy->execute();
		while($data_flat_vacancy = $result_for_flat_vacancy->fetchObject()){
			$flat_vacancy1[] = $data_flat_vacancy->estate_name;
			$flat_vacancy2[] = $data_flat_vacancy->block_name;
			$flat_vacancy3[] = $data_flat_vacancy->floor;
			$flat_vacancy[] = $data_flat_vacancy->flat_no;
			
			$flat_vacancy5[] = $data_flat_vacancy->flat_id;
		}
		
		for($i=0; $i<$no_of_vacancy; $i++) {
			$vacancy_details[] = array(
			'estate_name' => $flat_vacancy1[$i],
			'block_name' => $flat_vacancy2[$i],
			'floor' => $flat_vacancy3[$i],
			'flat_no' => $flat_vacancy[$i],
			'allotment_type' => $allotment_type, 
			'allotment_category' => $allotment_category_arr[$i], 
			'counter' => $roaster_counter_arr[$i],
			
			'flat_id' => $flat_vacancy5[$i],
			);		
		}
		
		return $vacancy_details;
		
		
	}

	function flat_roaster_details_pdf_page($flat_type = '', $no_of_vacancy = '', $file_name = '') {
		
		$flat_type = decrypt_url($flat_type);
		$no_of_vacancy = decrypt_url($no_of_vacancy);
		date_default_timezone_set("Asia/Kolkata");
		
		$vacancy_details = get_vacancy_details($flat_type, $no_of_vacancy);
		
		$page_output = '';
		
		$page_output = '<!doctype html>
		<html>
		<head>
		<meta charset="utf-8">
		<link rel="shortcut icon" href="http://localhost/eallotment/misc/favicon.ico" type="image/vnd.microsoft.icon" />
		<title>Allotee List</title>
		</head>	<body>	
		<div align="center">
			<img src="'.drupal_get_path('module', 'flat_roaster_details').'/images/govt_logo1.png" alt="Government Logo">
			<br>
			Housing Department
			<br>
			Government of West Bengal
			<br>
			1, K. S Roy Road, Kolkata - 700001
			<br>
			<font size="6"><b>e-Allotment of Rental Housing Estate</b></font>
			<br>
			<font size="5"><b>Flat Roaster Details</b></font>
		</div>
		<br>
		<div align="right">
			<font size="3"><b>Date : </b>'.date('l d-m-Y h:i:s A').'</font>
		</div>
		<br>
		<div>
			<table style="font-family: Arial, sans-serif; border: 1px solid black; border-collapse: collapse;" align="center" width="100%">
			<thead>
				<tr bgcolor="#999999">
					<th align="left" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat Type</b></font></th>
					<th align="center" width="30%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Name of the RHE</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Block</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Floor</b></font></th>
					<th align="center" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Flat No.</b></font></th>
					<th align="center" width="10%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Roaster Counter</b></font></th>
					<th align="right" width="15%" style="border: 1px solid black; border-collapse: collapse;"><font size="5"><b>Allotment Category</b></font></th>
				</tr>
			</thead>
		';
			foreach($vacancy_details as $val) {
				$page_output .='
			<tbody>
				<tr>';
					 if($val['allotment_type'] == 5)
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">A++</font></td>';
					 else if($val['allotment_type'] == 1)
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">A</font></td>';
					 else if($val['allotment_type'] == 2)
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">B</font></td>';
					 else if($val['allotment_type'] == 3)
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">C</font></td>';
					 else if($val['allotment_type'] == 4)
						$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">D</font></td>';
				
					$page_output .='<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['estate_name'].'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['block_name'].'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['floor'].'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['flat_no'].'</font></td>
					<td align="center" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['counter'].'</font></td>
					<td align="right" style="border: 1px solid black; border-collapse: collapse;"><font size="4">'.$val['allotment_category'].'</font></td>
				</tr></tbody>';
			}
			$page_output .='</table>
		</div></body>
</html>';
		//echo $page_output;
		ob_end_clean();
		return pdf_using_mpdf_api($page_output, $file_name);
		
		
		
		
		
	}