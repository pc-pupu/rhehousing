
		
	function validate_shifting_allotment_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"rhe_name":["RHE Name","selectBox"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			if(confirm("Are you sure you want to run Shifting Allotment process?")) {
				return true;
			} else {
				return false;
			}
		}
	}
	