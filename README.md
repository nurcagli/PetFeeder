### Sistemin İşleyişi

Proje, Mama kaplarının akıllı bir hale getirilmesi amaçlanarak tasarlanmıştır. Bunun için
mesafe sensörü, ağırlık sensörü ve bu ağırlık sensörü verilerine bağlı olarak çalışan bir servo
motor kullanılmıştır.
Mama kabının üst kısmında servo motor etkisiyle açılıp kapanan bir kapak ile alt kısımdan
ayrılan bir huni bulunmaktadır. Bu motor, mama kabının alt kısmındaki ağırlık sensörü
verileriyle mamanın miktarını algılar. Mamanın miktarı azaldığında çalışarak alt kısma mama
doldurulmasını sağlamaktadır.
Ağırlık sensörü verileri delayler kullanılarak belirli zaman aralıklarıyla ölçülmektedir. Ayrıca
mesafe sensörü de bu zaman içerisinde kaba uğrayan kedi sayısının ölçülme işleminde
kullanılmıştır. Bu iki veri ; kedi sayısı ve mama miktarı değişkenleri webhook kullanılarak
IFTTT ile twitter’a post atılmasında kullanılmıştır.
Verilerin saklanması ve anlamlı bir şekilde görüntülenmesi için ThingSpeak
Bulut Platformu kullanılarak değişiklikler izlenebilmektedir. Aynı zamanda Blynk
Uygulamasında sanal pin aracılığıyla ağırlık değeri görüntülenebilmekte ve servo
motor kontrolü yapılabilmektedir. 

