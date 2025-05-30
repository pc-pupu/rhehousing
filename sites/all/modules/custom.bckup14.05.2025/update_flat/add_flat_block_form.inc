<?php

	function add_flat_block_form($form, &$form_state) {
		
		$form['block_name'] = array(
			'#title' => t('Block Name'),
			//'#description' => t('Use this if block name not found in list.'),
			'#type' => 'textfield',
			'#default_value' => '',
			'#required' => TRUE,
			// '#prefix' => '<div class="two">', // 24-06-2024 sd
			// '#suffix' => '</div>', // 24-06-2024 sd
			'#attributes' => array('class' => array('form-control form-control-sm'),'oninput'=>"this.value=this.value.toUpperCase()"),//sd 24-06-2024
			'#prefix' => '<div class="col-md-12"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			'#element_validate' => array('validate_rhe_block'),
			//'#attributes' => array('oninput'=>"this.value=this.value.toUpperCase()"), //sd 24-06-2024
		);
		
		$form['submit'] = array(
			'#value' => t('Add'),
			'#type' => 'submit',
			// '#prefix' => '<div class="two" style="padding-top: 42px">',//sd 24-06-2024
			// '#suffix' => '</div>',//sd 24-06-2024
			'#prefix' => '<div class="col-md-12"><div class="form-floating">',//sd 24-06-2024
			'#suffix' => '</div></div>',//sd 24-06-2024
			'#attributes' => array('class' => array('btn bg-primary  px-5 rounded-pill text-white fw-bolder mb-2')),//sd 24-06-2024
	  	);
		
		$form['#attributes'] = array('onsubmit' => 'return validate_add_flat_block_form()');
	  	$form['#submit']= array('add_flat_block_submit');
		
		$form['all_list'] = array(
		   	'#type' => 'markup',
		   	'#markup' => viewRHEBlockList(),
			'#weight' => 50,
			'#prefix' => '<div style="margin-top:30px;">',
			'#suffix' => '</div>',
		);
		
		return $form;
	}
	
	function viewRHEBlockList() {
		$output = '';
		$result = rhe_block_list_full();
		//$rows =array(); // sd 24-06-2204
		//$header = array(); // sd 24-06-2204
		$header[] = array('data' => 'Sl. No.');
		$header[] = array('data' => 'Block Name');
		
		$i = 1;
		 while($data = $result->fetchObject()) {
			 $fields = array();
			 $fields[] = $i;
			 $fields[] = $data->block_name;
			 
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
			  '#attributes' => array(),
			);
		
			// Or, render using a theme function.
			$variables = array(
			  //'attributes' => array(),// sd 24-06-2024
			  'header' => $header,
			  'rows' => $rows,
			  'attributes'=> array('class'=>array('table table-list table-striped')),// sd 24-06-2024
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
							<table class="datatable_no_data_found table table-list table-striped">
								<tr class="tr_no_data_found">
									<th class="th_no_data_found"></th>
								</tr>
								<tr class="tr_no_data_found">
									<td class="td_no_data_found">No data found!</td>
								</tr>
							</table>
						</div>';
		}
		
		return '<div class ="mb-5 pb-3">'.$output.'</div>';
	}