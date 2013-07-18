<div class="<?= $classes; ?>"<?= $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?= $title_attributes; ?>><?= $label ?></div>
  <?php endif; ?>
  <div class="field-items"<?= $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
      <div class="field-item <?= $delta % 2 ? 'odd' : 'even'; ?>"<?= $item_attributes[$delta]; ?>><?= render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>