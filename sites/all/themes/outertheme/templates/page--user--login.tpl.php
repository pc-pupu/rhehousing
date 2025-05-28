<?php global $base_path, $base_root; ?>

<script src="<?php print $base_root.$base_path?>sites/all/themes/outertheme/js/crypto-js.min.js"></script> 
<script>
var CryptoJSAesJson = {
    stringify: function (cipherParams) {
        var j = {ct: cipherParams.ciphertext.toString(CryptoJS.enc.Base64)};
        if (cipherParams.iv) j.iv = cipherParams.iv.toString();
        if (cipherParams.salt) j.s = cipherParams.salt.toString();
        return JSON.stringify(j);
    },
    parse: function (jsonStr) {
        var j = JSON.parse(jsonStr);
        var cipherParams = CryptoJS.lib.CipherParams.create({ciphertext: CryptoJS.enc.Base64.parse(j.ct)});
        if (j.iv) cipherParams.iv = CryptoJS.enc.Hex.parse(j.iv)
        if (j.s) cipherParams.salt = CryptoJS.enc.Hex.parse(j.s)
        return cipherParams;
    }
}

function pwd_handler(form){	// alert(8888);
	//var x = form.pass.value;
	var password = document.getElementById('edit-pass').value;
	
	// var key = '<?php echo variable_get('api_secret_token'); ?>'; alert(key);
    var key = 'WBHOUSING12#$';
	var encrypted = CryptoJS.AES.encrypt(JSON.stringify(password), key, {format: CryptoJSAesJson}).toString();
	
	var j = JSON.parse(encrypted);
	
	jQuery("#edit-pass").val(j.iv);
	jQuery("#ct_val").val(j.ct);
	jQuery("#s_val").val(j.s);


    // Fetch API key securely
   /* jQuery.ajax({
        url: '/get-key',
        type: 'GET',
        dataType: 'json',
        success: function(response) {
            if (response.key) {
                var key = response.key;
                alert("Key fetched securely");

                var encrypted = CryptoJS.AES.encrypt(JSON.stringify(password), key, { format: CryptoJSAesJson }).toString();
                var j = JSON.parse(encrypted);

                jQuery("#edit-pass").val(j.iv);
                jQuery("#ct_val").val(j.ct);
                jQuery("#s_val").val(j.s);
            } else {
                alert("Error fetching key");
            }
        },
        error: function(error) {
            console.error("Error fetching key:", error);
        }
    });*/
	
}
</script>

<section class="admin-login-bg text-center">
    <div class="admin-login-top-bg">
        <div><a href="#" target="_self"><img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/admin-logo-rhe.png"
                    alt="e-Allotment of Rental Housing Estates" title="e-Allotment of Rental Housing Estates"></a>
        </div>
        <h2 class="mt-4">Admin Sign in to Continue</h2>
    </div>
    <div class="admin-login-white-bg text-start">
        <?php if ($messages): ?><?php print $messages; ?> <?php endif; ?>
        <?php   print render($page['content']); ?>
        <a href="<?= $base_root.$base_path ?>/user/password" target="_self">Forgot Password?</a>
    </div>
</section>