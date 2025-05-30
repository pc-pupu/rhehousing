jQuery(document).ready(function(){
		jQuery("#dop_vs").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		maxDate: "0",
		changeMonth: true,
		changeYear: true,
		yearRange: "-50:+0",
		autoSize: true
	});	
});

	
	
	function validate_vs_application_form(){
		//alert('OK'); 
		//return false;
		var formElements1 = validate_common_application_form();
		formElements2 =
		{
			"occupation_estate":["Select Housing","selectBox"],
			"occupation_block":["Select Block","selectBox"],
			"occupation_flat":["Flat No","selectBox"],
			"possession_date":["Date of Possession","date"],
			"files[file_licence]":["Upload Current Licence", "fileUpload"]
			
		};	
		var formElements = jQuery.extend(formElements1, formElements2);
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}		
	}