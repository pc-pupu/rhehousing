	
	function validate_rhe_allotment_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"allotment_type":["Allotment Type","selectBox"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			if(confirm("Are you sure you want to run Allotment process?")) {
				return true;
			} else {
				return false;
			}
		}
	}
	