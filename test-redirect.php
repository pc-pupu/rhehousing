<?php
while (ob_get_level()) {
    ob_end_clean();
}
header('Location: https://www.google.com', true, 302);
exit;
