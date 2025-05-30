jQuery(document).ready(function(){
		jQuery("#dop_cs").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		maxDate: "0",
		changeMonth: true,
		changeYear: true,
		yearRange: "-50:+0",
		autoSize: true
	});	
});

	function validate_cs_application_form(){
		//alert('OK'); 
		//return false;
		var formElements1 = validate_common_application_form();
		formElements2 =
		{
			"cs_occupation_estate":["Select Housing","selectBox"],
			"cs_occupation_block":["Select Block","selectBox"],
			"cs_occupation_flat":["Flat No","selectBox"],
			"cs_possession_date":["Date of Possession","date"],
			"files[cs_file_licence]":["Upload Current Licence", "fileUpload"]
			
		};	
		var formElements = jQuery.extend(formElements1, formElements2);
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}		
	}