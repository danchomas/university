import psycopg2
import random
from datetime import datetime, timedelta
from faker import Faker

fake = Faker('ru_RU')

# Connect to the database
conn = psycopg2.connect(
    dbname='railway',
    user='postgres',
    password='',  # Adjust if needed
    host='localhost'
)
cur = conn.cursor()

# Helper functions (same as before)

def random_string(length=10):
    letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    return ''.join(random.choice(letters) for _ in range(length))

def random_phone():
    return '+7' + ''.join(str(random.randint(0, 9)) for _ in range(10))

def random_email(i):
    return f'user{i}@example.com'

def random_passport():
    return f'{random.randint(1000, 9999)} {random.randint(100000, 999999)}'

def random_datetime():
    start = datetime(2025, 1, 1)
    end = datetime(2025, 12, 31)
    delta = end - start
    random_days = random.randint(0, delta.days)
    random_hours = random.randint(0, 23)
    random_minutes = random.randint(0, 59)
    return start + timedelta(days=random_days, hours=random_hours, minutes=random_minutes)

# Insert TicketStatus
statuses = ['активен', 'возвращен', 'забронирован']
for status in statuses:
    cur.execute("INSERT INTO TicketStatus (StatusName) VALUES (%s) ON CONFLICT (StatusName) DO NOTHING", (status,))
conn.commit()

cur.execute("SELECT ID FROM TicketStatus ORDER BY StatusName")
status_ids = [row[0] for row in cur.fetchall()]

# Insert Train (100 records)
train_types = ['скорый', 'пассажирский', 'фирменный']
train_ids = []
for i in range(100):
    train_number = f"{i+1:03}{random.choice('ABCDEFG')}"
    train_type = random.choice(train_types)
    cur.execute("INSERT INTO Train (TrainNumber, TrainType) VALUES (%s, %s) RETURNING ID", (train_number, train_type))
    train_ids.append(cur.fetchone()[0])
conn.commit()

# Insert Route (200 records)
stations = ['Москва', 'Санкт-Петербург', 'Казань', 'Екатеринбург', 'Новосибирск', 'Владивосток', 'Сочи', 'Калининград', 'Мурманск', 'Волгоград'] + [fake.city() for _ in range(20)]  # More stations for variety
route_ids = []
inserted_routes = set()
for _ in range(500):  # To get ~200 unique
    dep = random.choice(stations)
    arr = random.choice([s for s in stations if s != dep])
    if (dep, arr) in inserted_routes:
        continue
    inserted_routes.add((dep, arr))
    distance = random.randint(100, 5000)
    duration = random.randint(60, 1440)
    cur.execute("INSERT INTO Route (DepartureStation, ArrivalStation, Distance, DurationMinutes) VALUES (%s, %s, %s, %s) RETURNING ID", (dep, arr, distance, duration))
    route_ids.append(cur.fetchone()[0])
    if len(route_ids) >= 200:
        break
conn.commit()

# Insert ContactDetails (100000 records)
contact_ids = []
batch_size = 1000
for batch in range(0, 100000, batch_size):
    values = []
    for i in range(batch + 1, batch + batch_size + 1):
        fullname = f'Контакт {random_string(5)} {random_string(6)}'
        phone = random_phone()
        email = random_email(i)
        passport = random_passport()
        values.append((fullname, phone, email, passport))
    cur.executemany("INSERT INTO ContactDetails (FullName, Phone, Email, PassportData) VALUES (%s, %s, %s, %s) RETURNING ID", values)
    contact_ids.extend([row[0] for row in cur.fetchall()])
conn.commit()

# Insert Passenger (100000 records)
passenger_ids = []
for contact_id in contact_ids:
    cur.execute("INSERT INTO Passenger (ContactDetailsID) VALUES (%s) RETURNING ID", (contact_id,))
    passenger_ids.append(cur.fetchone()[0])
conn.commit()

# Insert Schedule (10000 records)
schedule_ids = []
for _ in range(10000):
    train_id = random.choice(train_ids)
    route_id = random.choice(route_ids)
    dep_time = random_datetime()
    duration_min = random.randint(60, 1440)
    arr_time = dep_time + timedelta(minutes=duration_min)
    cur.execute("INSERT INTO Schedule (TrainID, RouteID, DepartureDateTime, ArrivalDateTime) VALUES (%s, %s, %s, %s) RETURNING ID", (train_id, route_id, dep_time, arr_time))
    schedule_ids.append(cur.fetchone()[0])
conn.commit()

# Insert Car (50000 records)
car_types = ['плацкарт', 'купе', 'СВ', 'сидячий']
car_ids = []
car_seats = {}
for _ in range(50000):
    schedule_id = random.choice(schedule_ids)
    car_number = random.randint(1, 20)
    car_type = random.choice(car_types)
    total_seats = random.randint(18, 81)
    cur.execute("INSERT INTO Car (ScheduleID, CarNumber, CarType, TotalSeats) VALUES (%s, %s, %s, %s) RETURNING ID", (schedule_id, car_number, car_type, total_seats))
    car_id = cur.fetchone()[0]
    car_ids.append(car_id)
    car_seats[car_id] = total_seats
conn.commit()

# Insert Seat (500000 records)
seat_types = ['сидячее', 'лежачее']
seat_ids = []
for car_id, total_seats in car_seats.items():
    for seat_num in range(1, total_seats + 1):
        seat_type = random.choice(seat_types)
        cur.execute("INSERT INTO Seat (CarID, SeatNumber, SeatType) VALUES (%s, %s, %s) RETURNING ID", (car_id, seat_num, seat_type))
        seat_ids.append(cur.fetchone()[0])
conn.commit()

# Insert Ticket (100000 records)
for batch in range(0, 100000, batch_size):
    values = []
    for _ in range(batch_size):
        passenger_id = random.choice(passenger_ids)
        seat_id = random.choice(seat_ids)
        status_id = random.choice(status_ids)
        sale_time = random_datetime()
        price = round(random.uniform(1000, 10000), 2)
        values.append((passenger_id, seat_id, status_id, sale_time, price))
    cur.executemany("INSERT INTO Ticket (PassengerID, SeatID, StatusID, SaleDateTime, Price) VALUES (%s, %s, %s, %s, %s)", values)
conn.commit()

cur.close()
conn.close()

print("Данные сгенерированы успешно (100k+).")
