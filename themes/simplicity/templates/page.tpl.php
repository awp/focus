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
            <?= render($page['header']); ?>
            <nav id="navigation" role="navigation">
                <?= render($page['navigation']); ?>
            </nav>
        </div>
    </header>

    <div id="main">
        <div class="wrapper">
            <section id="content" role="main">
                <?= $breadcrumb; ?>
                <a id="main-content"></a>
                <?= render($title_prefix); ?>
                <?php if ($title): ?>
                    <h1 class="page--title title" id="page-title"><?= $title; ?></h1>
                <?php endif; ?>
                <?= render($title_suffix); ?>
                <?= render($page['content']); ?>
                <?= $feed_icons; ?>
            </section>

            <?php if ($sidebar = render($page['sidebar-first'])) { ?>
                <aside class="sidebar">
                    <?= $sidebar; ?>
                </aside>
            <?php } ?>
        </div>
    </div>

    <footer id="footer">
        <div class="wrapper">
            <?= render($page['footer']); ?>
        </div>
    </footer>

</div>

<?= render($page['bottom']); ?>
