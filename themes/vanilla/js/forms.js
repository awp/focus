(function($) {

    Drupal.behaviors.vanillaForms = {
        attach: function(cx, s) {
            if (!!$.fn.chosen) {
                var chzn = {
                    disable_search_threshold: 8
                }
                $('select').chosen(chzn);

                $('legend a').click(function() {
                    var fs = $(this).closest('fieldset');
                    $('.chzn-container', fs).remove();
                    $('select', fs).removeClass('chzn-done').show().chosen(chzn);
                });
            }

            if (!!$.fn.customFileInput) {
                $('input[type="file"]').customFileInput();
            }

            if (!!$.fn.placeholder) {
                $('input, textarea').placeholder();
            }

            $('form').submit(function() {
                $(this).addClass('processing');
            });
        }
    }

})(jQuery);
