<?php global $base_path, $base_root; ?>

<section class="admin-login-bg text-center">
    <div class="admin-login-top-bg">
        <div><a href="#" target="_self"><img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/admin-logo-rhe.png"
                    alt="e-Allotment of Rental Housing Estates" title="e-Allotment of Rental Housing Estates"></a>
        </div>
        <h2 class="mt-4">Reset Your Password</h2>
    </div>
    <div class="admin-login-white-bg text-start">
        <?php if ($messages): ?><?php print $messages; ?> <?php endif; ?>
        <?php   print render($page['content']);   ?>
        <a href="<?= $base_root.$base_path ?>/user/password" target="_self">Forgot Password?</a>
    </div>
    
</section>