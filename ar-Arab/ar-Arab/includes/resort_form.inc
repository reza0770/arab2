<option value="relevance">الصلة</option>
<optgroup label="الشعبية:">
 [% IF ( sort_by == "popularity_dsc" ) %]
 <option value="popularity_dsc" selected="selected">الشعبية (أكثر إلى أقلّ) </option>
 [% ELSE %]
 <option value="popularity_dsc">الشعبية (أكثر إلى أقلّ) </option>
 [% END %]
 [% IF ( sort_by == "popularity_asc" ) %]
 <option value="popularity_asc" selected="selected">الشعبية (أقلّ إلى أكثر) </option>
 [% ELSE %]
 <option value="popularity_asc">الشعبية (أقلّ إلى أكثر) </option>
 [% END %]
</optgroup>
<optgroup label="مؤلف">
 [% IF ( sort_by == "author_az" || sort_by == "author_asc" ) %]
 <option value="author_az" selected="selected">المؤلف (A-Z)</option>
 [% ELSE %]
 <option value="author_az">المؤلف (A-Z)</option>
 [% END %]
 [% IF ( sort_by == "author_za" || sort_by == "author_dsc" ) %]
 <option value="author_za" selected="selected">المؤلف (Z-A)</option>
 [% ELSE %]
 <option value="author_za">المؤلف (Z-A)</option>
 [% END %]
</optgroup>
<optgroup label="رقم الطلب">
 [% IF ( sort_by == "call_number_asc" ) %]
 <option value="call_number_asc" selected="selected">رقم الطلب (Z-A to 9-0)</option>
 [% ELSE %]
 <option value="call_number_asc">رقم الطلب (Z-A to 9-0)</option>
 [% END %]
 [% IF ( sort_by == "call_number_dsc" ) %]
 <option value="call_number_dsc" selected="selected">رقم الطلب (Z-A to 9-0)</option>
 [% ELSE %]
 <option value="call_number_dsc">رقم الطلب (Z-A to 9-0)</option>
 [% END %]
</optgroup>
<optgroup label="تواريخ">
 [% IF ( sort_by == "pubdate_dsc" ) %]
 <option value="pubdate_dsc" selected="selected">تاريخ النشر/حقوق الطبع والنشر:الاحدث الى الاقدم</option>
 [% ELSE %]
 <option value="pubdate_dsc">تاريخ النشر/حقوق الطبع والنشر:الاحدث الى الاقدم</option>
 [% END %]
 [% IF ( sort_by == "pubdate_asc" ) %]
 <option value="pubdate_asc" selected="selected">تاريخ النشر / حقوق الطبع والنشر  : الأقدم إلى الأحدث</option>
 [% ELSE %]
 <option value="pubdate_asc">تاريخ النشر / حقوق الطبع والنشر  : الأقدم إلى الأحدث</option>
 [% END %]
 [% IF ( sort_by == "acqdate_dsc" ) %]
 <option value="acqdate_dsc" selected="selected">تاريخ التزويد: من الاحدث الى الاقدم</option>
 [% ELSE %]
 <option value="acqdate_dsc">تاريخ التزويد: من الاحدث الى الاقدم</option>
 [% END %]
 [% IF ( sort_by == "acqdate_asc" ) %]
 <option value="acqdate_asc" selected="selected">تاريخ التزويد: من الاقدم الى الاحدث</option>
 [% ELSE %]
 <option value="acqdate_asc">تاريخ التزويد: من الاقدم الى الاحدث</option>
 [% END %]
</optgroup>
<optgroup label="عنوان">
 [% IF ( sort_by == "title_az" || sort_by == "title_asc" ) %]
 <option value="title_az" selected="selected">عنوان (A-Z)</option>
 [% ELSE %]
 <option value="title_az">عنوان (A-Z)</option>
 [% END %]
 [% IF ( sort_by == "title_za" || sort_by == "title_dsc" ) %]
 <option value="title_za" selected="selected">عنوان (Z-A)</option>
 [% ELSE %]
 <option value="title_za">عنوان (Z-A)</option>
 [% END %]
</optgroup>
