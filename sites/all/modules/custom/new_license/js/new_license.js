

	function validate_new_licence_form(){
		//alert('OK'); 
		//return false;
		var formElements1 = validate_common_application_form();
		formElements2 =
		{
			"files[file]":["Upload Necessary Document", "fileUpload"],
			"files[scaned_sign]":["Upload Your Scanned Signature","fileUpload"],
			
			"allotment_no":["Allotment No","no"],
			"allotment_date":["Allotment Date","date"],
			"allotment_district":["District","onlyAlphabet"],
			"allotment_estate":["Housing","streetAddress"],
			"allotment_address":["Housing Address", "housingAddress"]
			
		};	
		var formElements = jQuery.extend(formElements1, formElements2);
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}		
	}


