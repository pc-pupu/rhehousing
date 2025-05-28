<?php

	function viewFlatList($rhe_name = 0, $flat_type = 0, $block_name = 0) {
		global $base_path;
		
		$output = '';
		$result = rhe_flat_list_for_edit($rhe_name, $flat_type, $block_name);
		$rows = array();
		$header = array();
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'District');
		$header[] = array('data' => 'Flat Type');
		$header[] = array('data' => 'Name of the RHE');
		$header[] = array('data' => 'Estate Address');
		$header[] = array('data' => 'Block');
		$header[] = array('data' => 'Floor');
		$header[] = array('data' => 'Flat No');
		$header[] = array('data' => 'Flat Status');
		
		$i = 1;
		while($data = $result->fetchObject()) {
			 $fields = array();
			 $fields[] = $i;
			 $fields[] = $data->district_name;
			 $fields[] = $data->flat_type;
			 $fields[] = $data->estate_name;
			 $fields[] = $data->estate_address;
			 $fields[] = $data->block_name.' Block';
			 /*if($data->floor == 'Ground')
			 	$fields[] = 'Ground';
			 else if($data->floor == 'First')
			 	$fields[] = 'First';
			 else if($data->floor == 'Second')
			 	$fields[] = 'Second';
			 else if($data->floor == 'T')
			 	$fields[] = 'Third';
			 else if($data->floor == '')
			 	$fields[] = '';*/
			
			$fields[] = $data->floor;
			 $fields[] = $data->flat_no;

			if(isset($data->remarks)){
				$str = $data->flat_status_code."<br>"."(".$data->remarks.")";   //flat_status_code added by debaleena 26-07-2024
			}else{
				$str = $data->flat_status_code;   //flat_status_code added by debaleena 26-07-2024
			} 
			 
			 //if($data->is_occupied == FALSE) {
				//  $options['attributes']['class'] = array('button','small','round','link-button','steel_blue');
				$options['attributes']['class'] = array('btn bg-primary btn-sm px-5 mb-4 rounded-pill text-white fw-bolder');
				 $str.='</br></br>'.l('Edit', 'update_flat/edit/'.encrypt_url($data->flat_id),$options);
			 //}
			 /*else if($data->is_occupied == TRUE) {
				  $options['attributes']['class'] = array('button','small','round','link-button','steel_blue');
				  $options['attributes']['target'] = '_blank';
				  $options['attributes']['style'] = 'padding:7px;';
				  $options['html'] = TRUE;
				 $str.='</br></br>'.l('View', 'update_occupant/view/'.encrypt_url(fetch_occupant_id($data->flat_id)),$options);
			 }*/
			 $fields[] = $str;
			 
			 $rows[]  = $fields;
			 
			 $i++;
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
		
		if($result->rowCount() > 0) {
			// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array('class'=>array('table table-list table-striped')),
			);
		
			// Or, render using a theme function.
			$variables = array(
			  //'attributes' => array(),
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array('class'=>array('table table-list table-striped')),
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
	
		
		if($result->rowCount() > 0) {
			return /*l('<img height="18" width="18" src="'.$base_path.drupal_get_path('module', 'update_flat').'/images/pdf_icon.png" title="Download RHE Flat List" alt="PDF Icon">Download RHE Flat List','flat_list_pdf/flat_list_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).*/'<div class="mb-5 pb-3">'.$output.'</div>';
		}
		else {
			return '<div class="mb-5 pb-3">'.$output.'</div>';
		}
	}
