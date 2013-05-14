<div<?php print $attributes; ?>>
    <div<?php print $content_attributes; ?>>
        <?php if ($main_menu || $secondary_menu): ?>
            <nav class="navigation">
                <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix', 'main-menu')), 'heading' => array('text' => t('Main menu'),'level' => 'h2','class' => array('element-invisible')))); ?>
                <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix', 'secondary-menu')), 'heading' => array('text' => t('Secondary menu'),'level' => 'h2','class' => array('element-invisible')))); ?>
            </nav>
        <?php endif; ?>
        <?php if ($primary_local_tasks): ?>
            <div id="primary-tasks" class="clearfix<?php print $secondary_local_tasks ? ' with-secondary' : '' ?>" role="navigation">
                <ul class="tabs primary"><?php print render($primary_local_tasks); ?></ul>
            </div>
        <?php endif; ?>
        <?php if ($secondary_local_tasks): ?>
            <div class="secondary-tasks-wrapper">
                <div class="container">
                    <nav id="secondary-tasks" class="clearfix menu-wrapper" role="navigation">
                        <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
                    </nav>
                </div>
            </div>
        <?php endif; ?>
        <?php print $content; ?>
    </div>
</div>
