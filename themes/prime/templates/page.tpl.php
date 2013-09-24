<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728148
 */
?>

<div id="page">

    <header id="header" role="banner">
        <div class="wrapper">
            <?php print render($page['header']); ?>
            <?php if ($navigation = render($page['navigation'])) { ?>
                <nav id="navigation" role="navigation">
                    <?php print $navigation; ?>
                </nav>
            <?php } ?>
        </div>
    </header>

    <div id="main">
        <div class="wrapper">
            <section id="content" role="main">
                <?php print $breadcrumb; ?>
                <a id="main-content"></a>
                <?php print render($title_prefix); ?>
                <?php if ($title): ?>
                    <h1 class="page--title title" id="page-title"><?php print $title; ?></h1>
                <?php endif; ?>
                <?php print render($title_suffix); ?>
                <?php print render($page['content']); ?>
                <?php print $feed_icons; ?>
            </section>

            <?php if ($sidebar = render($page['sidebar'])): ?>
                <aside id="sidebar" class="sidebar" role="complimentary">
                    <?php print $sidebar; ?>
                </aside>
            <?php endif; ?>
        </div>
    </div>

    <?php if ($footer = render($page['footer'])) { ?>
        <footer id="footer">
            <div class="wrapper">
                <?php print $footer; ?>
            </div>
        </footer>
    <?php } ?>

</div>
