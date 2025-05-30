

	

	function validate_waiting_list(){
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