	
	/*jQuery(document).ready(function() {
		jQuery('.update_rhe_selectize').select2();
	});*/

	function validate_update_flat_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"rhe_name":["Name of the RHE","selectBox"],
			"flat_type":["Flat Type","selectBox"],
			"rhe_block":["Name of the Block","selectBox"],
			"flat_floor":["Floor No.","selectBox"],
			"flat_no":["Flat No.", "flatNo"],
			"flat_status":["Flat Status","selectBox"]
			
		};
		
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}	
	}
	
	function validate_add_flat_block_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"block_name":["Block Name","frontSlashHyphen"]
			
		};
		
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}	
	}