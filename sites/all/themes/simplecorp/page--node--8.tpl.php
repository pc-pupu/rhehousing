
<?php





?>

<!-- #page-wrapper -->
<div id="page-wrapper" style="overflow-x: hidden;">
<div id="overlay"></div>

    <!-- #page -->
    <div id="page">
        
        <!-- header -->
        <header role="header" class="container clearfix">
        
            <!-- #pre-header -->
            <div id="pre-header" class="clearfix">
            
                <?php if ($page['header']) :?>                
                <?php print render($page['header']); ?>
                <?php endif; ?>

                <?php if (theme_get_setting('social_icons_display','simplecorp')): ?>   
                    <!-- #social-icons -->
                    <div id="social-icons" class="clearfix">
                        <ul id="social-links">
                            <li class="facebook-link"><a href="https://www.facebook.com/morethan.just.themes" class="facebook" id="social-01" title="Join Us on Facebook!">Facebook</a></li>
                            <li class="twitter-link"><a href="https://twitter.com/morethanthemes" class="twitter" id="social-02" title="Follow Us on Twitter">Twitter</a></li>
                            <li class="google-link"><a href="#" id="social-03" title="Google" class="google">Google</a></li>
                            <li class="dribbble-link"><a href="#" id="social-04" title="Dribble" class="dribbble">Dribble</a></li>
                            <li class="vimeo-link"><a href="#" id="social-05" title="Vimeo" class="vimeo">Vimeo</a></li>
                            <li class="skype-link"><a href="#" id="social-06" title="Skype" class="skype">Skype</a></li>
                            <li class="linkedin-link"><a href="#" id="social-07" title="Linkedin" class="linkedin">Linkedin</a></li>
                            <li class="pinterest-link"><a href="#" id="social-09" title="Pinterest" class="pinterest">Pinterest</a></li>
                            <li class="rss-link"><a href="#" id="social-08" title="RSS" class="rss">RSS Feeds</a></li>
                        </ul>
                    </div>
                    <!-- EOF: #social-icons -->
                <?php endif; ?>    
                
            </div>
            <!-- EOF: #pre-header -->
      
            <!-- #header -->
            <div id="header" class="clearfix">
                
                <!-- #header-left -->
                <div id="header-left" class="one-third" style="margin-bottom:0px;"> 
                    
                    <?php if ($logo): ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                    <?php endif; ?>

                    <?php if (!$logo && ($site_name || $site_slogan)): ?>
                        <!-- #name-and-slogan -->
                        <hgroup id="name-and-slogan">
							<?php if ($site_name):?>
                            <h1 id="site-name"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1>
                            <?php endif; ?>
    
                            <?php if ($site_slogan):?>
                            <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
                            <?php endif; ?>
                        </hgroup> 
                        <!-- EOF:#name-and-slogan -->
                    <?php endif; ?>

                </div>
                <!--EOF: #header-left -->     

                <!-- #header-right -->
                <div id="header-right" class="two-third last" style="margin-bottom:0px;">   
					
                    <!-- #navigation-wrapper -->
                    
                    <?php 
						date_default_timezone_set("Asia/Kolkata");
						print date("l\, jS F Y\, h:i:s A"); 
					?>
                    
                    <!-- EOF: #navigation-wrapper -->

                </div>
                <!--EOF: #header-right -->

            </div> 
            <!-- EOF: #header -->
            <?php /*?><div id="navigation-wrapper" class="clearfix">
                        <!-- #main-navigation -->                        
                        <nav id="main-navigation" class="main-menu clearfix" role="navigation">
                        <?php if ($page['navigation']) :?>
                        <?php print drupal_render($page['navigation']); ?>
                        <?php else : ?>

                        <?php if (module_exists('i18n_menu')) {
                        $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
                        } else { $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu')); }
                        print drupal_render($main_menu_tree); ?>

                        <?php endif; ?>
                        </nav>
                        <!-- EOF: #main-navigation -->
                    </div><?php */?>

        </header>   
        <!-- EOF: header -->

        <div id="content" class="clearfix">

            <?php if ($page['top_content']): ?>
            <!-- #top-content -->
            <div id="top-content" class="container clearfix">
              <!-- intro-page -->
              <div class="intro-page">
              <?php print render($page['top_content']); ?>
              </div>
              <!-- EOF: intro-page -->            
            </div>  
            <!--EOF: #top-content -->
            <?php endif; ?>
            
            <!-- #banner -->
            <div id="banner" class="container">

                <?php if ($page['banner']) : ?>
                <!-- #banner-inside -->
                <div id="banner-inside">
                <?php print render($page['banner']); ?>
                </div>
                <!-- EOF: #banner-inside -->        
                <?php endif; ?>

                <?php if (theme_get_setting('slideshow_display','simplecorp')): ?>

					<?php if ($is_front): ?>
                    <!-- #slider-container -->
                    <div id="slider-container">
                        <div class="flexslider loading">
                            <ul class="slides">
    
                                <!-- first-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-16.jpg" alt="RHE Banner 1" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                                <!-- second-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                        
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-17.jpg" alt="RHE Banner 2" /></a>
                                    </div>                        
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                                <!-- third-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-18.jpg" alt="RHE Banner 3" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
                                 <!-- fourth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-19.jpg" alt="RHE Banner 4" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
                                 <!-- fifth-slide -->
                                <li class="slider-item">
                                    <div class="slider-image">                            
                                        <a href="<?php print base_path();?>"><img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/sampleimages/banner-20.jpg" alt="RHE Banner 5" /></a>
                                    </div>
                                    <div class="flex-caption">
                                        <h3>e-Allotment of Rental Housing Estate</h3>
                                    </div>
                                </li>
    
                            </ul>
                        </div>
                    </div>
                    <!-- EOF: #slider-container -->
                    <?php endif; ?>

                <?php endif; ?>
            
            </div>

            <!-- EOF: #banner -->
            <?php if ($breadcrumb && theme_get_setting('breadcrumb_display','simplecorp')):?>
            <!-- #breadcrumb -->
            <div class="container clearfix">
            <?php print $breadcrumb; ?>
            </div>
            <!-- EOF: #breadcrumb -->
            <?php endif; ?>

            <?php if ($messages):?>
            <!--messages -->
            <div class="container clearfix">
            <?php print $messages; ?>
            </div>
            <!--EOF: messages -->        
            <?php endif; ?>

            <div><?php print 'Hello' ?></div>
            
            <!--#main-content -->
            <div id="main-content" class="container clearfix" align="center">
				<?php /*?><?php print render($page['content']); ?><?php */?>
                <img src="<?php print base_path() . drupal_get_path('theme', 'simplecorp') ;?>/images/under_construction.jpg" alt="Under Construction" />
            </div> 
<!-- EOF: #page-wrapper -->
<?php
if(user_is_logged_in()) {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'#main-navigation .menu li:last-child\').removeClass(\'last\');
		jQuery(\'#main-navigation .menu li:last-child\').after(\'<li class="last leaf ulogout"><a href="' . $base_url . $base_path . 'user/logout' . '">Logout</a></li>\');
	});', 'inline');
} else {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'#main-navigation .menu li:last-child\').removeClass(\'last\');
		jQuery(\'#main-navigation .menu li:last-child\').after(\'<li class="last leaf ulogin"><a href="' . $base_url . $base_path . 'user' . '">Login</a></li>\');
	});', 'inline');
}

if(arg(0) == 'user' && arg(1) == '') {
	drupal_add_js('jQuery(document).ready(function(e) {
		jQuery(\'.ulogin a\').addClass(\'active\');
	});', 'inline');	
}
?>
