jQuery(document).ready(function(){
	
    jQuery(".toggle-menu").click(function(){
        jQuery(this).parent("li").children("ul").toggle(300);
    });
});