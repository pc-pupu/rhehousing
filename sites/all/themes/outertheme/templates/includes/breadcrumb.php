<?php global $base_path,$base_root;?>
<div class="d-flex flex-row justify-content-between">
    <div class="title">
        <h3 class="title-lg"><?= $title?></h3>
        <ul class="breadcrumb text-muted fs-6 fw-normal ms-1">
        <li class="breadcrumb-item text-muted"><a href="dashboard" class="text-muted text-hover-primary">Home</a></li>
        <li class="breadcrumb-item text-dark"><?= $title?></li>
        </ul>
    </div>
    <div class="dropdown">
        <a href="#" class="d-flex align-items-center text-decoration-none dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
        <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/profile_icon.png" alt="" width="50" height="50" class="rounded-circle me-2">
        <div class="user-name">
            <strong><?php echo $user->name;?></strong></br>
            
        </div>
        </a>
        <ul class="dropdown-menu text-small shadow" style="">
        <li><a class="dropdown-item" href="<?= $base_root.$base_path.'user-profile' ?>">Profile</a></li>
        
        </ul>
    </div>
</div>