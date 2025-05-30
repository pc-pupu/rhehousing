<?php
/*all housing list*/
function all_housing_list($flat_type_id = 0, $flat_category_id = 0) {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he',
		'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd',
		'he.district_code = hd.district_code');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id', $flat_type_id, '=');
	$db_and->condition('hf.flat_category_id', $flat_category_id, '=');
	$query->condition($db_and);
	
	$query->groupBy('hf.estate_id');
	$query->groupBy('he.estate_name');
	$query->groupBy('he.estate_address');
	$query->groupBy('hd.district_name');
	
	$query->orderBy('district_name', 'ASC');
	$query->orderBy('estate_id', 'ASC');
	
	//$query->extend('TableSort')->extend('PagerDefault')->limit(1);
	//echo $query;
	return $query->execute();
}	

/*rhe flat vacancy list*/
function rhe_flat_allotment_list($district_id = 0, $flat_type_id = 0, $flat_status_id = 0) {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd', 'hd.district_code = he.district_code');
	$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	$query->addField('hft', 'flat_type');
	
	$db_and = db_and();
	$db_and->condition('he.district_code', $district_id,'=');
	$db_and->condition('hf.flat_type_id', $flat_type_id, '=');
	$db_and->condition('hf.flat_status_id', $flat_status_id, '=');
	$query->condition($db_and);
	
	$query->groupBy('hf.estate_id');
	$query->groupBy('he.estate_name');
	$query->groupBy('he.estate_address');
	$query->groupBy('hd.district_name');
	$query->groupBy('hft.flat_type');
	$query->orderBy('district_name', 'ASC');
	$query->orderBy('estate_id', 'ASC');
	//$query->extend('TableSort')->extend('PagerDefault')->limit(1);
	//echo $query;
	return $query->execute();
}

/*rhe total no of flat vacancy*/
function rhe_total_flat_vacancy($district_id = '', $flat_type_id = '', $flat_status_id = '') {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd', 'hd.district_code = he.district_code');
	$query->innerJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	$query->addField('hft', 'flat_type');
	
	$db_and = db_and();
	$db_and->condition('he.district_code', $district_id,'=');
	$db_and->condition('hf.flat_type_id', $flat_type_id, '=');
	$db_and->condition('hf.flat_status_id', $flat_status_id, '=');
	$query->condition($db_and);
	
	return $query->execute();
}
	
function rhe_flat_allotment_list_rst_estate_list($flat_type_id = 0, $flat_status_id = 0, $estate_id = 0) {
	$query = db_select('housing_flat', 'hf');
	$query->addField('hf','flat_id');
	$query->addField('hf','flat_no');
	$query->addField('hf','floor');
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id', $flat_type_id, '=');
	$db_and->condition('hf.flat_status_id', $flat_status_id, '=');
	$db_and->condition('hf.estate_id', $estate_id, '=');
	$query->condition($db_and);
	$query->orderBy('estate_id', 'ASC');
	$query->orderBy('flat_id', 'ASC');
	//echo $query;
	//die($query);
	return $query->execute();
}
function rhe_flat_allotment_list_rst_estate($flat_type_id = 0, $flat_status_id = 0, $estate_id = 0) {

	$result = rhe_flat_allotment_list_rst_estate_list($flat_type_id, $flat_status_id, $estate_id);
	$output = array();
	$output[] = $result->rowCount();
	$str = '';
	if($result->rowCount() > 0){
		$i = 0;
		while($data = $result->fetchObject()){
			
			if(trim($data->floor) == 'G') {
				$floor = 'Ground Flr.';	
			}
			else if(trim($data->floor) == 'F') {
				$floor = '<b>1st Flr.</b>';	
			} else if(trim($data->floor) == 'S') {
				$floor = '<b>2nd Flr.</b>';	
			} else if(trim($data->floor) == 'T') {
				$floor = 'Top Flr.';	
			}
			
			if($i == 0){
				$str.=$data->flat_no.'('.$floor.')';
				$i++;
			}else{
				$str.=', '.$data->flat_no.'('.$floor.')';
			}
		}
	}

	
	$output[] = $str;
	return $output; 
}

function rhe_flat_status($flat_status_id = 0) {
	$query=db_select('housing_flat_status','hfs');
	$query->addField('hfs','flat_status');
	$query->condition('hfs.flat_status_id',$flat_status_id,'=');
	
	return $query->execute();
}
