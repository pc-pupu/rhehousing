jQuery(document).ready(function(){
	
    jQuery(".label").click(function(){
        //jQuery(this).parent("h6").children("div").toggle(300);
		jQuery(this).parent("h6").parent("td").parent("tr").children("td").children("h6").children("div").toggle(300);
    });
});

