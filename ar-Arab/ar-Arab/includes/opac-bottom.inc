[% USE raw %]
[% USE Koha %]
[% USE AdditionalContents %]
[%- USE KohaPlugins -%]
[% USE Asset %]
[% SET opaccredits = AdditionalContents.get( location => "opaccredits", lang => lang, library => branchcode ) %]
[% PROCESS 'html_helpers.inc' %]
[% UNLESS ( is_popup ) %]
 [% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
 [% IF ( opaccredits ) %]
 <div class="container-fluid">
 <div class="row">
 <div class="col">
 [% PROCESS koha_news_block news => opaccredits %]
 </div>
 </div>
 </div>
 [% END #/ opaccredits %]

 [% IF ( Koha.Preference('OPACReportProblem') && Koha.Preference('KohaAdminEmailAddress') ) || OpacKohaUrl %]
 <div class="container-fluid">
 <div class="row">
 <div class="col">
 <div id="report-koha-url">
 <div class="row justify-content-between">
 [% IF Koha.Preference('OPACReportProblem') && Koha.Preference('KohaAdminEmailAddress') %]
 <div class="col">
 <div id="report_a_problem" class="noprint">
 <a class="koha-url" href="/cgi-bin/koha/opac-reportproblem.pl">الإبلاغ عن مشكلة</a>
 </div>
 </div>
 [% END # / IF Koha.Preference('OPACReportProblem') && Koha.Preference('KohaAdminEmailAddress') %]
 [% IF OpacKohaUrl %]
 <div class="col">
 <div id="koha_url" class="clearfix noprint">
 <p>مدعوم بواسطة [% IF template.name.match('opac-main.tt') %] <a class="koha_url" href="http://koha-community.org">كوها</a>
 [% ELSE %]
 <a class="koha_url" rel="nofollow" href="http://koha-community.org">كوها</a>
 [% END %]</p>
 </div> <!-- /#koha_url -->
 </div> <!-- /.col -->
 [% END # /IF OpacKohaUrl %]
 </div> <!-- /.row.justify-content-between -->
 </div> <!-- /#report-koha-url -->
 </div> <!-- /.col -->
 </div> <!-- /.row -->
 </div> <!-- /.container-fluid -->
 [% END # / OPACReportProblem || OpacKohaUrl %]
 </div> <!-- / #wrapper in masthead.inc -->

 [% IF OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer' %]
 [% IF ( opaclanguagesdisplay ) %]
 [% IF ( languages_loop && opaclanguagesdisplay ) %]
 [% UNLESS ( one_language_enabled ) %]
 <footer id="changelanguage"  class="noprint">
 <ul class="nav">
 <li class="nav-item">
 <span class="navbar-text">اللغات:</span>
 </li>
 [% FOREACH languages_loo IN languages_loop %]
 [% IF ( languages_loo.group_enabled ) %]
 [% IF ( languages_loo.plural ) %]
 <li class="nav-item dropup">
 <a class="nav-link dropdown-toggle" href="#" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" id="show[% languages_loo.rfc4646_subtag | html %]">
 [% IF ( languages_loo.native_description ) %]
 [% languages_loo.native_description | html %]
 [% ELSE %]
 [% languages_loo.rfc4646_subtag | html %]
 [% END %]
 </a><!-- /.nav-link.dropdown-toggle -->
 <div id="sub[% languages_loo.rfc4646_subtag | html %]" class="dropdown-menu" aria-labelledby="show[% languages_loo.rfc4646_subtag | html %]">
 [% FOREACH sublanguages_loo IN languages_loo.sublanguages_loop %]
 [% IF ( sublanguages_loo.enabled ) %]
 [% IF ( sublanguages_loo.sublanguage_current ) %]
 <a class="dropdown-item" href="#">[% sublanguages_loo.native_description | html %] [% sublanguages_loo.script_description | html %] [% sublanguages_loo.region_description | html %] [% sublanguages_loo.variant_description | html %] ([% sublanguages_loo.rfc4646_subtag | html %])</a>
 [% ELSE %]
 <a class="dropdown-item" href="/cgi-bin/koha/opac-changelanguage.pl?language=[% sublanguages_loo.rfc4646_subtag | uri %]"> [% sublanguages_loo.native_description | html %] [% sublanguages_loo.script_description | html %] [% sublanguages_loo.region_description | html %] [% sublanguages_loo.variant_description | html %] ([% sublanguages_loo.rfc4646_subtag | html %])</a>
 [% END %]
 [% END # / IF sublanguages_loo.enabled %]
 [% END # / FOREACH sublanguages_loo %]
 </div> <!-- /#sub[% languages_loo.rfc4646_subtag | html %] -->
 </li> <!-- /.nav-item.dropup -->
 [% ELSE %]
 [% IF ( languages_loo.group_enabled ) %]
 [% IF ( languages_loo.current ) %]
 <li class="nav-item">
 <a class="nav-link disabled" href="#" tabindex="-1" aria-disabled="true">
 [% IF ( languages_loo.native_description ) %]
 [% languages_loo.native_description | html %]
 [% ELSE %]
 [% languages_loo.rfc4646_subtag | html %]
 [% END %]
 </a> <!-- /.nav-link -->
 </li> <!-- /.nav-item -->
 [% ELSE %]
 <li class="nav-item">
 <a class="nav-link" href="/cgi-bin/koha/opac-changelanguage.pl?language=[% languages_loo.rfc4646_subtag | uri %]">
 [% IF ( languages_loo.native_description ) %]
 [% languages_loo.native_description | html %]
 [% ELSE %]
 [% languages_loo.rfc4646_subtag | html %]
 [% END %]
 </a> <!-- /.nav-link -->
 </li> <!-- /.nav-item -->
 [% END # /IF ( languages_loo.current ) %]
 [% END # / IF languages_loo.current %]
 [% END # / IF ( languages_loo.plural ) %]
 [% END # / IF ( languages_loo.group_enabled ) %]
 [% END # / FOREACH languages_loo IN languages_loop %]
 </ul> <!-- /.nav -->
 </footer> <!-- / #changelanguage -->
 [% END # / UNLESS ( one_language_enabled ) %]
 [% END # / IF ( languages_loop && opaclanguagesdisplay ) %]
 [% END # / IF opaclanguagesdisplay %]
 [% END # /IF OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer' %]
[% END # / UNLESS is_popup %]

<!-- JavaScript includes -->
[% Asset.js("lib/jquery/jquery-3.4.1.min.js") | $raw %]
[% Asset.js("lib/jquery/jquery-migrate-3.1.0.min.js") | $raw %]
[% Asset.js("lib/jquery/jquery-ui-1.12.1.min.js") | $raw %]
<script>
// Resolve name collision between jQuery UI and Twitter Bootstrap
$.widget.bridge('uitooltip', $.ui.tooltip);
</script>
[% Asset.js("lib/bootstrap/js/bootstrap.bundle.min.js") | $raw %]
[% Asset.js("lib/fontfaceobserver.min.js") | $raw %]
[% Asset.js("js/global.js") | $raw %]
<script>
    Modernizr.load([
        // Test need for polyfill
        {
            test: window.matchMedia,
            nope: "[% Asset.url('lib/media.match.min.js') | $raw %]"
        },
        // and then load enquire
        "[% Asset.url('lib/enquire.min.js') | $raw %]",
        "[% Asset.url('js/script.js') | $raw %]",
    ]);

    // Fix for datepicker in a modal
    $.fn.modal.Constructor.prototype.enforceFocus = function () {};
</script>
[% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
<script>
        var NO_AMAZON_IMAGE = _("لا توجد صورة غلاف متاحة");

</script>
[% Asset.js("js/amazonimages.js") | $raw %]
[% END %]

<script>

    var MSG_CONFIRM_AGAIN = _("تحذير: لا يمكنك التراجع. من فضلك أكد رغبتك بذلك مرةً أخرى")
    var MSG_DELETE_SEARCH_HISTORY = _("هل أنت متأكد من أنك تريد حذف سِجل بحثك؟");
    var MSG_NO_SUGGESTION_SELECTED = _("لم يتم تحديد أي مقترح");
    var MSG_SEARCHING = _("جاري البحث %s...");
    var MSG_ERROR_SEARCHING_COLLECTION = _("خطأ أثناء بحث مجموعة %s ");
    var MSG_NO_RESULTS_FOUND_IN_COLLECTION = _("لم يتم العثور على نتائج في مجموعة %s بالمكتبة");
    var MSG_RESULTS_FOUND_IN_COLLECTION = _("تم العثور على %s نتيجة في مجموعة %s بالمكتبة");
    var MSG_BY = _("بواسطة");
    var MSG_TYPE = _("نوع");
    var MSG_NEXT = _("التالى");
    var MSG_PREVIOUS = _("السابق");
    var MSG_CHECKOUTS = _("الإعارات");
    var MSG_NO_CHECKOUTS = _("لا توجد إعارات");
    var MSG_CHECK_OUT = _("إعارة");
    var MSG_CHECK_OUT_CONFIRM = _("هل أنت متأكد من أنك تريد إعارة هذه المادة؟");
    var MSG_CHECKED_OUT_UNTIL = _("معار حتى %s");
    var MSG_CHECK_IN = _("الإعادة (الرد)");
    var MSG_CHECK_IN_CONFIRM = _("هل أنت متأكد من أنك تريد إعادة هذه المادة؟");
    var MSG_NO_CHECKOUTS = _("لا توجد إعارات");
    var MSG_DOWNLOAD = _("تنزيل");
    var MSG_HOLDS = _("الحجوزات ");
    var MSG_NO_HOLDS = _("لا توجد حجوزات");
    var MSG_PLACE_HOLD = _("إحجز");
    var MSG_CANCEL_HOLD = _("إلغاء");
    var MSG_CANCEL_HOLD_CONFIRM = _("هل أنت متأكد من أنك تريد إلغاء هذا الحجز؟");
    var MSG_ON_HOLD = _("محجوز");

    [% IF ( Koha.Preference( 'opacuserlogin' ) == 1 ) && ( Koha.Preference( 'TagsEnabled' ) == 1 ) %]
        var MSG_TAGS_DISABLED = _("عذرا ، الوسوم غير مفعلة في هذا النظام.");
        var MSG_TAG_ALL_BAD = _("خطأ! الوسم المدخل هو رمز محظور. لم يتم إضافته . يرجى المحاولة مرة أخرى مع نص عادي.");
        var MSG_ILLEGAL_PARAMETER = _("خطأ :معامل غير مشروع");
        var MSG_TAG_SCRUBBED = _("ملاحظة: يحتوي وسمك على رمز تم حذفه. تمت إضافة الوسم كـ");
        var MSG_ADD_TAG_FAILED = _("خطأ! فشلت إضافة الوسوم في");
        var MSG_ADD_TAG_FAILED_NOTE = _("ملاحظة: يمكنك وسم المادة بمصطلح معين مرة واحدة فقط. تحقق من 'وسومي' لرؤية وسومك الحالية.");
        var MSG_DELETE_TAG_FAILED = _("خطأ : لا يمكنك حذف الوسم");
        var MSG_DELETE_TAG_FAILED_NOTE = _("ملاحظة: يمكنك حذف فقط الأوسمة الخاصة بك.")
        var MSG_LOGIN_REQUIRED = _("يجب تسجيل دخولك لكي تضيف وسوم.");
        var MSG_TAGS_ADDED = _("الوسوم المضافة:");
        var MSG_TAGS_DELETED = _("الوسوم المضافة:");
        var MSG_TAGS_ERRORS = _("أخطاء: ");
        var MSG_MULTI_ADD_TAG_FAILED = _("غير قادر على إضافة واحد أو أكثر من العلامات.");
        var MSG_NO_TAG_SPECIFIED = _("لا يوجد وسم محدد.");
    [% END %]
    [% IF ( Koha.Preference('OverDriveClientKey') && Koha.Preference('OverDriveClientSecret') ) %]
        var MSG_OVERDRIVE_LOGIN = _("سجل الدخول إلى حسابك");
        var MSG_OVERDRIVE_LINK = _( "صفحة الحساب" );
        var MSG_OVERDRIVE_LOGOUT = _("سجل الخروج من حسابك");
        var MSG_OVERDRIVE_CHECKEDOUT_UNTIL = _( "مستعار حتى:" );
        var MSG_OVERDRIVE_ACCESS_ONLINE = _("متاح على الخط المباشر");
        var MSG_OVERDRIVE_DOWNLOAD_AS = _( "التنزيل كـ:" );
        var MSG_OVERDRIVE_CANNOT_CHECKOUT = _("المادة لا يمكن اعارتها: لا توجد تسجيلة متاحة");
    [% END %]
    [% IF OpenLibraryCovers || OpenLibrarySearch %]
        var NO_OL_JACKET = _("لا توجد صورة غلاف متاحة");
    [% END %]
    [% IF (query_desc) %]
        var query_desc = "[% query_desc | html %]";
        var querystring = "[% querystring | html %]";
        var query_cgi = "[% query_cgi | html %]";
    [% END %]

    [% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
        $(window).load(function() {
            verify_images();
         });
    [% END %]
    $(".print-large").on("click",function(){
        window.print();
        return false;
    });
    $(".addtoshelf").on("click",function(e){
        e.preventDefault();
        Dopop( this.href );
    });
    $("body").on("click", ".addtocart", function(e){
        e.preventDefault();
        var biblionumber = $(this).data("biblionumber");
        addRecord( biblionumber );
    });
    $("body").on("click", ".cartRemove", function(e){
        e.preventDefault();
        var biblionumber = $(this).data("biblionumber");
        delSingleRecord( biblionumber );
    });
    $(".clearsh").on("click", function(){
        return confirmDelete(MSG_DELETE_SEARCH_HISTORY);
    });

</script>

[% IF Koha.Preference( 'opacbookbag' ) == 1 %]
 [% Asset.js("js/basket.js") | $raw %]
[% ELSIF ( Koha.Preference( 'virtualshelves' ) == 1 ) %]
 [% Asset.js("js/basket.js") | $raw %]
[% ELSE %]
 <script>var readCookie;</script>
[% END %]

[% IF Koha.Preference( 'opacuserlogin' ) == 1 %][% IF Koha.Preference( 'TagsEnabled' ) == 1 %][% Asset.js("js/tags.js") | $raw %][% END %][% ELSE %][% END %]
[% IF ( GoogleJackets ) %]
 [% Asset.js("js/google-jackets.js") | $raw %]
 <script>

        var NO_GOOGLE_JACKET = _("لا توجد صورة غلاف متاحة");

    </script>
[% END %]
[% IF ( Koha.Preference('OpacCoce') && Koha.Preference('CoceProviders') ) %]
 [% Asset.js("js/coce.js") | $raw %]
 <script>

        var NO_COCE_JACKET = _("لا توجد صورة غلاف متاحة");

    </script>
[% END %]

[% IF OPACLocalCoverImages %]
 [% Asset.js("js/localcovers.js") | $raw %]
 <script>

    var NO_LOCAL_JACKET = _("لا توجد صورة غلاف متاحة");

    </script>
[% END %]

[% IF ( BakerTaylorEnabled ) %]
 [% Asset.js("js/bakertaylorimages.js") | $raw %]
 <script>

        var NO_BAKERTAYLOR_IMAGE = _("لا توجد صورة غلاف متاحة");
        $(window).load(function(){
            bt_verify_images();
        });

    </script>
[% END %]

[% IF Koha.Preference( 'OpacNewsLibrarySelect' ) %]
<script>
    $("#news-branch-select").change(function() {
        $( "#news-branch-select" ).submit();
    });
</script>
[% END %]

[% IF Koha.Preference('RecordedBooksClientSecret') && Koha.Preference('RecordedBooksLibraryID') %]
<script>
  var SPINNER_THROBBER = "[% interface | html %]/lib/jquery/plugins/themes/classic/throbber.gif";
</script>
[% END %]

[% Asset.js("lib/jquery/plugins/jquery.cookie.min.js") | $raw %]
<script>
$(document).ready(function() {
    if($('#searchsubmit').length) {
        $(document).on("click", '#searchsubmit', function(e) {
            jQuery.removeCookie("form_serialized", { path: '/'});
            jQuery.removeCookie("form_serialized_limits", { path: '/'});
            jQuery.removeCookie("num_paragraph", { path: '/'});
            jQuery.removeCookie("search_path_code", { path: '/'});
        });
    }
});
</script>
[% PROCESS jsinclude %]
[% IF ( Koha.Preference('OPACUserJS') ) %]
 <script>
        [% Koha.Preference('OPACUserJS') | $raw %]
    </script>
[% END %]
[% IF SCO_login %]
 [% SET SCOUserJS = Koha.Preference('SCOUserJS') %]
 [% IF ( SCOUserJS ) %]
 <script>

            [% SCOUserJS | $raw %]

        </script>
 [% END %]
[% END %]
[% KohaPlugins.get_plugins_opac_js | $raw %]
</body>
</html>
