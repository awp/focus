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

    <?php if ($logo): ?>
      <a href="<?= $front_page; ?>" title="<?= t('Home'); ?>" rel="home" class="header--logo" id="logo"><img src="<?= $logo; ?>" alt="<?= t('Home'); ?>" class="header--logo-image" /></a>
    <?php endif; ?>

    <?php if ($site_name || $site_slogan): ?>
      <div class="header--name-and-slogan" id="name-and-slogan">
        <?php if ($site_name): ?>
          <h1 class="header--site-name" id="site-name">
            <a href="<?= $front_page; ?>" title="<?= t('Home'); ?>" class="header--site-link" rel="home"><span><?= $site_name; ?></span></a>
          </h1>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <h2 class="header--site-slogan" id="site-slogan"><?= $site_slogan; ?></h2>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if ($secondary_menu): ?>
      <nav class="header--secondary-menu" id="secondary-menu" role="navigation">
        <?= theme('links__system_secondary_menu', array(
          'links' => $secondary_menu,
          'attributes' => array(
            'class' => array('links', 'inline', 'clearfix'),
          ),
          'heading' => array(
            'text' => $secondary_menu_heading,
            'level' => 'h2',
            'class' => array('element-invisible'),
          ),
        )); ?>
      </nav>
    <?php endif; ?>

    <?= render($page['header']); ?>

  </header>

  <div id="main">

    <div id="content" class="column" role="main">
      <?= render($page['highlighted']); ?>
      <?= $breadcrumb; ?>
      <a id="main-content"></a>
      <?= render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page--title title" id="page-title"><?= $title; ?></h1>
      <?php endif; ?>
      <?= render($title_suffix); ?>
      <?= $messages; ?>
      <?= render($tabs); ?>
      <?= render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?= render($action_links); ?></ul>
      <?php endif; ?>
      <?= render($page['content']); ?>
      <?= $feed_icons; ?>
    </div>

    <div id="navigation">

      <?php if ($main_menu): ?>
        <nav id="main-menu" role="navigation">
          <?php
          // This code snippet is hard to modify. We recommend turning off the
          // "Main menu" on your sub-theme's settings form, deleting this PHP
          // code block, and, instead, using the "Menu block" module.
          // @see http://drupal.org/project/menu_block
          print theme('links__system_main_menu', array(
            'links' => $main_menu,
            'attributes' => array(
              'class' => array('links', 'inline', 'clearfix'),
            ),
            'heading' => array(
              'text' => t('Main menu'),
              'level' => 'h2',
              'class' => array('element-invisible'),
            ),
          )); ?>
        </nav>
      <?php endif; ?>

      <?= render($page['navigation']); ?>

    </div>

    <?php
      // Render the sidebars to see if there's anything in them.
      $sidebar_first  = render($page['sidebar_first']);
      $sidebar_second = render($page['sidebar_second']);
    ?>

    <?php if ($sidebar_first || $sidebar_second): ?>
      <aside class="sidebars">
        <?= $sidebar_first; ?>
        <?= $sidebar_second; ?>
      </aside>
    <?php endif; ?>

  </div>

  <?= render($page['footer']); ?>

</div>

<?= render($page['bottom']); ?>
