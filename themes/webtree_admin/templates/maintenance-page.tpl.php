<?php
/**
 * @file
 * Override of the default maintenance page.
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?= $language->language ?>" lang="<?= $language->language ?>" dir="<?= $language->dir ?>">
<head>
    <title><?= $site_name ?></title>
    <?= $head ?>
    <?= $styles ?>
    <?= $scripts ?>
</head>
<body class="<?= $classes ?>">
    
    <div id="wide-wrapper">
        <div id="sticky-wrapper">

            <header id="section-header" class="section section-header">
                <div class="section-wrapper">
                    <a href="<?= $base_path; ?>">
                        <div id="logo">
                            <?= $site_logo; ?>
                        </div>
                        <div id="name">
                            <?= $site_name; ?>
                        </div>
                    </a>
                </div>
                <div class="section-wrapper">
                    <?= $messages; ?>
                </div>
            </header>
            
            <section id="section-content" class="section section-content">
                <div class="section-wrapper">
                    <?php if (!empty($sidebar_first)) { ?>
                        <div id="region-sidebar-left" class="region region-sidebar-left">
                            <div class="region-inner">
                                <?= $sidebar_first ?>
                            </div>
                        </div>
                    <?php } ?>
            
                    <div id="region-content" class="region region-content">
                        <div class="region-inner">
                            <?= $content; ?>
                        </div>
                    </div>
            
                    <?php if (!empty($sidebar_second)) { ?>
                        <div id="region-sidebar-right" class="region region-sidebar-right">
                            <div class="region-inner">
                                <?= $sidebar_second ?>
                            </div>
                        </div>
                    <?php } ?>
                </div>
            </section>
        
        </div><!-- #sticky-wrapper -->
        
        <footer id="section-footer" class="section section-footer">
            <div class="section-wrapper">
                <?= $footer ?>
            </div>
        </footer>
        
    </div><!-- #wide-wrapper -->
    
</body>
</html>
