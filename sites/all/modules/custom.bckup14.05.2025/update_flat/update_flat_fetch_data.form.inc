<?php
/*fetch all RHE */
  	function rhe_list() {

		$rhe_options = array(''=>'- Select -');
		$query = db_select('housing_estate', 'he')->fields('he');
		$query->orderBy('estate_name','ASC');
		$result = $query->execute();
		foreach($result as $val) {
			$str = $val->estate_name;
			if($val->estate_address != null){
				$str = $str.' | '.$val->estate_address;
			}
			$rhe_options[$val->estate_id] = $str;
		}
		
		return $rhe_options;
	}
/*fetch all RHE flat type list*/
  	function rhe_flat_type() {

		$rhe_flat_type_options = array('' => '- Select -');
		$query = db_select('housing_flat_type', 'hft')->fields('hft')->orderBy('hft.flat_type', 'ASC');
		$result = $query->execute();
		foreach($result as $val) {
			$rhe_flat_type_options[$val->flat_type_id] = $val->flat_type;
		}
		
		return $rhe_flat_type_options;
	}
/*fetch all flat_status */
  	function flat_status_list() {

		$flat_status_options = array(''=>'- Select -');
		$query = db_select('housing_flat_status', 'hfs')->fields('hfs');
		//$query->condition('hfs.is_occupied', FALSE, '=');
		$query->condition('hfs.is_active', 1);
		//$query->condition('hfs.flat_status', 'occupied', '!=');    //added by debaleena 30-12-2024
		//$query->condition('hfs.flat_status', 'vacant_due_to_release', '!=');  //added by debaleena 30-12-2024
		//$query->condition('hfs.flat_status', 'occupied_but_unauthorized', '!=');  //added by debaleena 07-01-2025
		$result = $query->execute();
		foreach($result as $val) {
			$flat_status_options[$val->flat_status_id] = $val->flat_status_code;  //flat_status_code added by debaleena 26-07-2024
		}
		// print_r($flat_status_options);die;
		return $flat_status_options;
	}
	
/*fetch all block list*/
	function rhe_block_list() {
		$rhe_block_options = array(''=>'- Select -');
		$query = db_select('housing_block', 'hb')->fields('hb')->orderBy('block_name', 'ASC');
		$result = $query->execute();
		foreach($result as $val) {
			$rhe_block_options[$val->block_id] = $val->block_name;
		}
	
		return $rhe_block_options;
	}
	
	function rhe_block_list_full() {
		$query = db_select('housing_block', 'hb')->fields('hb')->orderBy('block_name', 'ASC');
		return $query->execute();
	}

/*fetch all RHE flat list*/
  	function rhe_flat_list($flat_type_id = 0, $status_id = 0) {

		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he',
			'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hd',
			'he.district_code = hd.district_code');
		$query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query->innerJoin('housing_flat_status', 'hfs',
			'hfs.flat_status_id = hf.flat_status_id');
		$query->innerJoin('housing_flat_type', 'hft',
			'hft.flat_type_id = hf.flat_type_id');
		$query->addField('hf', 'flat_id');
		$query->addField('hf', 'flat_no');
		$query->addField('hf', 'estate_id');
		$query->addField('hf', 'flat_type_id');
		$query->addField('hf', 'block_id');
		$query->addField('hf', 'floor');
		$query->addField('hf', 'flat_status_id');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$query->addField('hb', 'block_name');	
		$query->addField('hfs', 'flat_status');
		$query->addField('hfs', 'is_occupied');
		$query->addField('hft', 'flat_type');
		if($flat_type_id != 0 && $status_id != 0){
			$db_and = db_and();
			$db_and->condition('hf.flat_type_id',$flat_type_id,'=');
			$db_and->condition('hf.flat_status_id',$status_id,'=');
			$query->condition($db_and);
		}
		
		$query->orderBy('is_occupied', 'ASC');
		//$query->orderBy('flat_type', 'ASC');
		$query->orderBy('he.district_code', 'ASC');
		$query->orderBy('estate_id', 'ASC');
		//$query->orderBy('flat_no', 'ASC');
		$query->orderBy('flat_id', 'ASC');
		
		//echo $query;
		return $query->execute();
	}
	
	function rhe_flat_list_for_edit($rhe_name, $flat_type, $block_name) {
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');
		$query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query->innerJoin('housing_flat_status', 'hfs', 'hfs.flat_status_id = hf.flat_status_id');
		$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
		$query->addField('hf', 'flat_id');
		$query->addField('hf', 'flat_no');
		$query->addField('hf', 'estate_id');
		$query->addField('hf', 'flat_type_id');
		$query->addField('hf', 'block_id');
		$query->addField('hf', 'floor');
		$query->addField('hf', 'flat_status_id');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$query->addField('hb', 'block_name');	
		$query->addField('hfs', 'flat_status');
		$query->addField('hfs', 'flat_status_code');
		$query->addField('hfs', 'is_occupied');
		$query->addField('hft', 'flat_type');
		$query->addField('hf','remarks');
		if($rhe_name != 0 && $flat_type != 0 && $block_name != 0){
			$db_and = db_and();
			$db_and->condition('hf.estate_id', $rhe_name, '=');
			$db_and->condition('hf.flat_type_id', $flat_type, '=');
			$db_and->condition('hf.block_id', $block_name, '=');
			$query->condition($db_and);
		}
		
		$query->orderBy('is_occupied', 'ASC');
		//$query->orderBy('flat_type', 'ASC');
		$query->orderBy('he.district_code', 'ASC');
		$query->orderBy('estate_id', 'ASC');
		//$query->orderBy('flat_no', 'ASC');
		$query->orderBy('flat_id', 'ASC');
		
		//echo $query;
		return $query->execute();		
	}
	
/*fetch all RHE flat list*/
	function rhe_flat_list_rst_id($id = '') {
		if ($id !== '' && (!is_numeric($id) || $id <= 0)) {
			$id = 0;
		}
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he','he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hd','he.district_code = hd.district_code');
		$query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query->innerJoin('housing_flat_status', 'hfs','hfs.flat_status_id = hf.flat_status_id');
		$query->innerJoin('housing_flat_type', 'hft','hft.flat_type_id = hf.flat_type_id');
		$query->addField('hf', 'flat_id');
		$query->addField('hf', 'flat_no');
		$query->addField('hf', 'estate_id');
		$query->addField('hf', 'flat_type_id');
		$query->addField('hf', 'block_id');
		$query->addField('hf', 'floor');
		$query->addField('hf', 'flat_status_id');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$query->addField('hb', 'block_name');	
		$query->addField('hfs', 'flat_status');
		$query->addField('hft', 'flat_type');
		$query->condition('hf.flat_id', $id, '=');
		return $query->execute();
	}

	function fetch_flat_status_id($flat_status = ''){
		$query = db_select('housing_flat_status', 'hfs');
		$query->addField('hfs','flat_status_id');
		$query->condition('hfs.flat_status',trim($flat_status), '=');
		$result =$query->execute();
		
		$data = $result->fetchObject();
		return $data->flat_status_id;
	}
	
//RHE wise flat list	
	function rhe_wise_flat_list_detail($rhe_name = '') {
		
		$query = db_select('housing_flat', 'hf');
		$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
		$query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');
		$query->innerJoin('housing_block', 'hb', 'hb.block_id = hf.block_id');
		$query->innerJoin('housing_flat_status', 'hfs', 'hfs.flat_status_id = hf.flat_status_id');
		$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
		$query->addField('hf', 'flat_id');
		$query->addField('hf', 'flat_no');
		$query->addField('hf', 'estate_id');
		$query->addField('hf', 'flat_type_id');
		$query->addField('hf', 'block_id');
		$query->addField('hf', 'floor');
		$query->addField('hf', 'flat_status_id');
		$query->addField('he', 'estate_name');
		$query->addField('he', 'estate_address');
		$query->addField('hd', 'district_name');
		$query->addField('hb', 'block_name');	
		$query->addField('hfs', 'flat_status');
		$query->addField('hfs', 'flat_status_code');
		$query->addField('hfs', 'is_occupied');
		$query->addField('hft', 'flat_type');
		$query->addField('hf', 'remarks');
		
		if($rhe_name != 0){
			$db_and = db_and();
			$db_and->condition('he.estate_id',$rhe_name,'=');
			$query->condition($db_and);
		}
		
		$query->orderBy('flat_id', 'ASC');
		
		//echo $query;
		return $query->execute();	
		
	}
