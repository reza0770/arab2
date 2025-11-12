[% USE Koha %]
<script>
        var debug    = "[% debug | html %]";
        var dformat  = "[% dateformat | html %]";
        var sentmsg = 0;
        if (debug > 1) {alert("dateformat: " + dformat + "\ndebug is on (level " + debug + ")");}

        function Date_from_syspref(dstring) {
                var dateX = dstring.split(/[-/.]/);
                if (debug > 1 && sentmsg < 1) {sentmsg++; alert("Date_from_syspref(" + dstring + ") splits to:\n" + dateX.join("\n"));}
                if (dformat === "iso") {
                        return new Date(dateX[0], (dateX[1] - 1), dateX[2]);  // YYYY-MM-DD to (YYYY,m(0-11),d)
                } else if (dformat === "us") {
                        return new Date(dateX[2], (dateX[0] - 1), dateX[1]);  // MM/DD/YYYY to (YYYY,m(0-11),d)
                } else if (dformat === "metric") {
                        return new Date(dateX[2], (dateX[1] - 1), dateX[0]);  // DD/MM/YYYY to (YYYY,m(0-11),d)
                } else if (dformat === "dmydot") {
                        return new Date(dateX[2], (dateX[1] - 1), dateX[0]);  // DD.MM.YYYY to (YYYY,m(0-11),d)
                } else {
                        if (debug > 0) {alert("KOHA ERROR - Unrecognized date format: " +dformat);}
                        return 0;
                }
        }

        /* Instead of including multiple localization files as you would normally see with
           jQueryUI we expose the localization strings in the default configuration */
        jQuery(function($){
            $.datepicker.regional[''] = {
                closeText: _("تم التنفيذ"),
                prevText: _("السابق"),
                nextText: _("التالى"),
                currentText: _("يوم"),
                monthNames: [_("يناير"),_("نيسان"),_("مارس"),_("ابريل"),_("مايو"),_("يونية"),
                _("يوليو"),_("آب"),_("سبتمبر"),_("أكتوير"),_("نوفمبر"),_("كانون الأول")],
                monthNamesShort: [_("يناير"), _("شهر نيسان"), _("مارس"), _("ابريل"), _("مايو"), _("يونية"),
                _("يوليو"), _("آب"), _("سبتمبر"), _("أكتوبر"), _("Nov"), _("Dec")],
                dayNames: [_("الأحد"), _("الإثنين"), _("الثلاثاء"), _("الاربعاء"), _("الخميس"), _("الجمعة"), _("السبت")],
                dayNamesShort: [_("اﻷحد"), _("الإثنين"), _("الثلاثاء"), _("الاربعاء"), _("الخميس"), _("الجمعة"), _("السبت")],
                dayNamesMin: [_("الأحد"),_("الاثنين"),_("الثلاثاء"),_("الأربعاء"),_("الخميس"),_("الجمعة"),_("السبت")],
                weekHeader: _("أسبوع"),
                dateFormat: '[% IF ( dateformat == "us" ) %]mm/dd/yy[% ELSIF ( dateformat == "metric" ) %]dd/mm/yy[% ELSIF ( dateformat == "dmydot" ) %]dd.mm.yy[% ELSE %]yy-mm-dd[% END %]',
                firstDay: [% Koha.Preference('CalendarFirstDayOfWeek') | html %],
                isRTL: [% IF ( bidi ) %]true[% ELSE %]false[% END %],
                showMonthAfterYear: false,
                yearSuffix: ''};
            $.datepicker.setDefaults($.datepicker.regional['']);
        });

        $(document).ready(function(){

        $.datepicker.setDefaults({
                showOn: "both",
                changeMonth: true,
                changeYear: true,
                buttonImage: '[% interface | html %]/lib/famfamfam/calendar.png',
                buttonImageOnly: true,
                showButtonPanel: true,
                showOtherMonths: true,
                yearRange: "c-100:c+10"
            });

        $("#borrower_dateofbirth").datepicker({
                yearRange: "c-100:c"
            });

            $( ".datepicker" ).datepicker();
            // http://jqueryui.com/demos/datepicker/#date-range
            var dates = $( ".datepickerfrom, .datepickerto" ).datepicker({
                changeMonth: true,
                numberOfMonths: 1,
                onSelect: function( selectedDate ) {
                    var option = this.id == "from" ? "minDate" : "maxDate",
                        instance = $( this ).data( "datepicker" );
                        date = $.datepicker.parseDate(
                            instance.settings.dateFormat ||
                            $.datepicker._defaults.dateFormat,
                            selectedDate, instance.settings );
                    dates.not( this ).datepicker( "option", option, date );
                }
            });
        });

        // jQuery Datepicker - a11y: Map arrow keys
        var doKeyDown = $.datepicker._doKeyDown
        $.extend($.datepicker, {
            _doKeyDown: function(event) {
                if (event.which === $.ui.keyCode.LEFT ||
                    event.which === $.ui.keyCode.RIGHT ||
                    event.which === $.ui.keyCode.UP ||
                    event.which === $.ui.keyCode.DOWN) {
                    event.ctrlKey = true;
                    doKeyDown(event);
                } else {
                    doKeyDown(event);
                }
            }
        });
</script>
