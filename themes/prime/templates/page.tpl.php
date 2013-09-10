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

    <header class="header" id="header" role="banner">
        <div class="wrapper">
            <?php print render($page['header']); ?>
            <nav id="navigation" role="navigation">
                <?php print render($page['navigation']); ?>
            </nav>
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

            <?php if ($sidebar_first = render($page['sidebar_first'])): ?>
                <aside class="primary-sidebar">
                    <?php print $sidebar_first; ?>
                </aside>
            <?php endif; ?>

            <?php if ($sidebar_second = render($page['sidebar_second'])): ?>
                <section class="secondary-sidebar">
                    <?php print $sidebar_second; ?>
                </section>
            <?php endif; ?>

            <?php if ($postscript = render($page['postscript'])): ?>
                <section class="postscript">
                    <?php print $postscript; ?>
                </section>
            <?php endif; ?>
        </div>
    </div>

    <footer id="footer">
        <div class="wrapper">
            <?php print render($page['footer_left']); ?>
            <?php print render($page['footer_right']); ?>
        </div>
    </footer>

</div>

<?php print render($page['bottom']); ?>
