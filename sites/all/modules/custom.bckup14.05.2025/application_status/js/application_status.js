

	function validate_application_status_form(){
		//alert('OK');
		var formElements =
		{
			"application_no":["Application No","textBox"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}