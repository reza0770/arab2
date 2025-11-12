[% USE raw %]
[% USE Asset %]
[% Asset.js("lib/jquery/plugins/jquery.dataTables.min.js") | $raw %]
<script>
    var MSG_DT_FIRST = _("أولا");
    var MSG_DT_LAST = _("الأخير");
    var MSG_DT_NEXT = _("التالى");
    var MSG_DT_PREVIOUS = _("السابق");
    var MSG_DT_EMPTY_TABLE = _("لا توجد بيانات متاحة في الجدول");
    var MSG_DT_INFO = _("عرض _البداية_ إلى _النهاية_ من _المجموع_");
    var MSG_DT_INFO_EMPTY = _("لا مُدخلات ليتم عرضها");
    var MSG_DT_INFO_FILTERED = _("(filtered from _MAX_ total entries)");
    var MSG_DT_LENGTH_MENU = _("اظهر _القائمة_ مدخلات");
    var MSG_DT_LOADING_RECORDS = _("التحميل...");
    var MSG_DT_PROCESSING = _("جاري تنفيذ العملية...");
    var MSG_DT_SEARCH = _("بحث:");
    var MSG_DT_ZERO_RECORDS = _("لم يعثر على تسجيلات مطابقة");
    var MSG_DT_COPY_TO_CLIPBOARD = _("نسخ إلى الحافظة");
    var MSG_DT_COPY_KEYS = _("قم بالضغط على <i>ctrl</i> or <i>⌘</i> + <i>C</i> لنسخ بيانات الجدول<br>إلى حافظة نظامك.<br><br>للإلغاء، قم بالنقر على هذه الرسالة أو الضغط على مفتاح escape.");
    var MSG_DT_COPIED_ROWS = _("تم نسخ %d صفاً إلى الحافظة");
    var MSG_DT_COPIED_ONE_ROW = _("تم نسخ صف واحد إلى الحافظة");
    var MSG_CLEAR_FILTER = _("مسح المنقح");
    var MSG_DT_ALL = _("كل");
    var CONFIG_EXCLUDE_ARTICLES_FROM_SORT = _("a an the");
</script>
[% Asset.js("js/datatables.js") | $raw %]
