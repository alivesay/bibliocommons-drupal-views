<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php if (empty($fields['name']->raw)): ?>
  <div class="bibliocommons-list-item">
    <a href="<?= $fields['title_details_url']->raw; ?>" title="<?= $fields['title_title']->raw; ?>"><img class="bibliocommons-list-item-jacket" alt="<?= $fields['title_title']->raw; ?>" src="<?= $jacket_img_url ?>" /></a>
    <div class="bibliocommons-list-item-info">
      <span class="bibliocommons-list-item-info-title">
        <a href="<?= $fields['title_details_url']->raw; ?>" title="<?= $fields['title_title']->raw; ?>"><?= $fields['title_title']->raw; ?></a>

      </span>
      <span class="bibliocommons-list-item-info-author">
      <?= $author_line; ?>
      </span>
      <span class="bibliocommons-list-item-info-pub">
      (<strong><?= $fields['title_format_name']->raw; ?></strong> - <?= $publication_date; ?>)
      </span>
      <span class="bibliocommons-list-item-info-availability">
      <?php
        if ($available_count > 0) {
          print '<span class="bibliocommons-list-item-available">Available to borrow </span>';
          print '<a href="http://mylibrary.bibliocommons.com/item/show_circulation/' . $fields['title_id']->raw . '?search_scope=mylibrary">in some Locations</a>';
        } else {
          print '<span class="bibliocommons-list-item-unavailable">All copies in use </span>';
          print '<a href="http://mylibrary.bibliocommons.com/item/show_circulation/' . $fields['title_id']->raw . '?search_scope=mylibrary">Availability details</a>';
        }
      ?>
      </span>
    </div>
  </div>
<?php endif; ?>
