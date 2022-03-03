import requests
import pandas as pd
from bs4 import BeautifulSoup
import time
import datetime
import telegram.ext
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters

bot_token = '5199818345:AAGNYfdyxGuGEaB9ZISHO6LJSRWbGW8IUxY'
bot = telegram.Bot(token='5199818345:AAGNYfdyxGuGEaB9ZISHO6LJSRWbGW8IUxY')

list1 = {}
listglobal = {'DAY' : [], 'WEEK' : [], 'TIME' : [], 'PRICE' : [], 'TEMPERATURE' : [], 'WIND' : [], 'WEATHER' : []}

def telegram_bot_sendtext(bot_message):

    
    bot_token = '5199818345:AAGNYfdyxGuGEaB9ZISHO6LJSRWbGW8IUxY'
    bot_chatID = '761022353'
    send_text = 'https://api.telegram.org/bot' + bot_token + '/sendMessage?chat_id=' + bot_chatID + '&parse_mode=Markdown&text=' + bot_message

    response = requests.get(send_text)


    return response.json()

def on_message(update, context):
    global listglobal
    chat = update.effective_chat
    text = update.message.text
    list1 = eval(text)
    for k, v in list1.items():
        if k in listglobal:
            listglobal[k].append(v)
        else:
            listglobal[k] = v
    print(listglobal)





updater = Updater(bot_token, use_context=True)
dispatcher = updater.dispatcher
dispatcher.add_handler(MessageHandler(Filters.all, on_message))



while 1==1:
    updater.start_polling()
    dtime = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
    data = int(dtime[14]+dtime[15])
    if(data % 5 == 0):
        Time = []
        Day = []
        Week = []
        Price = []
        Temperature = []
        Wind = []
        Weather = []

        taxi = 'https://yandex.by/maps/157/minsk/?ll=27.541621%2C53.860281&mode=routes&rtext=53.864738%2C27.486160~53.919101%2C27.593496&rtt=taxi&ruri=ymapsbm1%3A%2F%2Ftransit%2Fstop%3Fid%3Dstation__9891255~ymapsbm1%3A%2F%2Fgeo%3Fll%3D27.594%252C53.919%26spn%3D0.001%252C0.001%26text%3D%25D0%2591%25D0%25B5%25D0%25BB%25D0%25B0%25D1%2580%25D1%2583%25D1%2581%25D1%258C%252C%2520%25D0%259C%25D1%2596%25D0%25BD%25D1%2581%25D0%25BA%252C%2520%25D0%25B2%25D1%2583%25D0%25BB%25D1%2596%25D1%2586%25D0%25B0%2520%25D0%259F%25D0%25B5%25D1%2582%25D1%2580%25D1%2583%25D1%2581%25D1%258F%2520%25D0%2591%25D1%2580%25D0%25BE%25D1%259E%25D0%25BA%25D1%2596%252C%25204&z=13.16'
        response1 = requests.get(taxi)
        weather = 'https://www.meteoprog.by/ru/weather/Minsk/'
        response2 = requests.get(weather)
        soup1 = BeautifulSoup(response1.text, 'lxml')
        soup2 = BeautifulSoup(response2.text, 'lxml')
        price = soup1.find('div', class_='taxi-route-snippet-view__price')
        temperature = soup2.find('div', class_='today-temperature')
        wind = soup2.find_all('td', class_='atmosphere-spec')[1]
        weath = soup2.find('h3')
        tim = soup2.find('h2')

        s1 = ''
        s2 = ''
        s3 = ''
        s4 = ''
        s5 = ''
        s6 = ''
        s7 = ''
        s8 = ''
        s11 = ''
        s22 = ''
        for quote in price:
            s1 += quote.text
        i = 1;
        while s1[i] != '\u202f':
            s11 += s1[i]
            i += 1
        for quote in temperature:
            s2 += quote.text
        i = 0
        while s2[i] != '-' and s2[i] != '+' and s2[i] != '0':
            i += 1
        while s2[i] != ' ':
            s22 += s2[i]
            i += 1
        for quote in wind:
            s3 += quote.text
        for quote in weath:
            s4 += quote.text
        for quote in tim:
            s5 += quote.text
        for i in range(5):
            s6 += s5[16 + i]
        i = 0
        while s5[24+i] != ',':
            s7 += s5[24 + i]
            i = i + 1
        i += 26
        while i < len(s5):
            s8 += s5[i]
            i += 1

        Price.append(s11)
        Temperature.append(s22)
        Wind.append(s3)
        Weather.append(s4)
        Time.append(s6)
        Day.append(s7)
        Week.append(s8)

        list = {'Day' : Day, 'Week' : Week, 'Time' : Time, 'Price' : Price, 'Temperature' : Temperature, 'Wind' : Wind, 'Weather' : Weather}


        test = telegram_bot_sendtext(str(list).upper())
        time.sleep(100)

df = pd.DataFrame(list)
df.to_excel('./taxi.xlsx', index=False)


