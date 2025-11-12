[% USE Koha %]
[% USE Branches %]
[% PROCESS 'html_helpers.inc' %]

<div id="search-facets">
 <form method="get" action="/cgi-bin/koha/opac-topissues.pl">
 <h2><a href="#" class="menu-collapse-toggle">تنقيح بحثك</a></h2>
 <ul class="menu-collapse">
 <li><label for="limit">عرض أعلى </label>
 <select name="limit" id="limit">
 [% IF ( limit == 10 ) %]<option value ="10" selected="selected">10 عناوين</option>[% ELSE %]<option value="10">10 عناوين</option>[% END %]
 [% IF ( limit == 15 ) %]<option value ="15" selected="selected">15عنوان</option>[% ELSE %]<option value="15">15عنوان</option>[% END %]
 [% IF ( limit == 20 ) %]<option value ="20" selected="selected">20 عنوان</option>[% ELSE %]<option value="20">20 عنوان</option>[% END %]
 [% IF ( limit == 30 ) %]<option value ="30" selected="selected">30 عنوان</option>[% ELSE %]<option value="30">30 عنوان</option>[% END %]
 [% IF ( limit == 40 ) %]<option value ="40" selected="selected">40 عنوان</option>[% ELSE %]<option value="40">40 عنوان</option>[% END %]
 [% IF ( limit == 50 ) %]<option value ="50" selected="selected">50 عنوان</option>[% ELSE %]<option value="50">50 عنوان</option>[% END %]
 [% IF ( limit == 100 ) %]<option value ="100" selected="selected">100 عنوان</option>[% ELSE %]<option value="100">100 عنوان</option>[% END %]
 </select></li>

 [% IF Branches.all.size > 1 %]
 <li><label for="branch">من:</label>
 <select name="branch" id="branch">
 <option value="">كل المكتبات</option>
 [% PROCESS options_for_libraries libraries => Branches.all( selected => branch ) %]
 </select></li>
 [% END %]

 [% AdvancedSearchTypes = Koha.Preference('AdvancedSearchTypes').split('\|') %]
 [% IF AdvancedSearchTypes.grep('^itemtypes$').size %]
 <li>
 <label for="itemtype">حدّد إلى: </label>
 <select name="itemtype" id="itemtype">
 <option value="">كل أنواع المادة</option>
 [% FOREACH itemtype IN ItemTypes.Get() %]
 [% IF itemtype.itemtype == selected_itemtype %]
 <option value="[% itemtype.itemtype | html %]" selected="selected">
 [% ELSE %]
 <option value="[% itemtype.itemtype | html %]">
 [% END %]
 [% itemtype.translated_description | html %]
 </option>
 [% END %]
 </select>
 </li>
 [% END %]

 [% IF AdvancedSearchTypes.grep('^ccode$').size %]
 <li>
 <label for="ccode">حدّد إلى: </label>
 <select name="ccode" id="ccode">
 <option value="">كل المجموعات</option>
 [% FOREACH ccode IN AuthorisedValues.Get('CCODE', 1) %]
 [% IF ccode.authorised_value == selected_ccode %]
 <option value="[% ccode.authorised_value | html %]" selected="selected">
 [% ELSE %]
 <option value="[% ccode.authorised_value | html %]">
 [% END %]
 [% ccode.lib | html %]
 </option>
 [% END %]
 </select>
 </li>
 [% END %]

 <li><label for="timeLimit">مكتسب في آخر:</label>
 <select name="timeLimit" id="timeLimit">
 [% IF ( timeLimit == 3 ) %]
 <option value="3" selected="selected">3 أشهر</option>
 [% ELSE %]
 <option value="3">3 أشهر</option>
 [% END %]
 [% IF ( timeLimit == 6 ) %]
 <option value="6" selected="selected">6 أشهر</option>
 [% ELSE %]
 <option value="6">6 أشهر</option>
 [% END %]
 [% IF ( timeLimit == 12 ) %]
 <option value="12" selected="selected">12 شهراً</option>
 [% ELSE %]
 <option value="12">12 شهراً</option>
 [% END %]
 [% IF ( timeLimit == 999 ) %]
 <option value="999" selected="selected">لا يوجد حدود</option>
 [% ELSE %]
 <option value="999">لا يوجد حدود</option>
 [% END %]
 </select></li>
 <li>
 <input type="hidden" name="do_it" value="1" />
 <input class="btn btn-primary" type="submit" value="إرسال" />
 </li>
 </ul>
 </form>
</div>
