== Layouts/Regions ==

Add a partial here for each region that may be included in a layout. If all
layouts include all regions, it may be simpler to include region layouts all in
the global partial.

=== global.scss ===

There may be layout styles that transcend any one specific region, such as a
wrapper or container class. The global partial should be included in any layout
requiring the use of these more global layout styles.