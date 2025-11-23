from sqlalchemy import Column, Integer, String, ForeignKey, DateTime, Numeric
from sqlalchemy.orm import relationship, declarative_base

Base = declarative_base()


class Train(Base):
    __tablename__ = "train"
    id = Column(Integer, primary_key=True)
    trainnumber = Column(String)
    traintype = Column(String)
    schedules = relationship("Schedule", back_populates="train")


class Route(Base):
    __tablename__ = "route"
    id = Column(Integer, primary_key=True)
    departurestation = Column(String)
    arrivalstation = Column(String)
    schedules = relationship("Schedule", back_populates="route")


class Schedule(Base):
    __tablename__ = "schedule"
    id = Column(Integer, primary_key=True)
    trainid = Column(Integer, ForeignKey("train.id"))
    routeid = Column(Integer, ForeignKey("route.id"))
    departuredatetime = Column(DateTime)
    train = relationship("Train", back_populates="schedules")
    route = relationship("Route", back_populates="schedules")
    cars = relationship("Car", back_populates="schedule")


class Car(Base):
    __tablename__ = "car"
    id = Column(Integer, primary_key=True)
    scheduleid = Column(Integer, ForeignKey("schedule.id"))
    cartype = Column(String)
    totalseats = Column(Integer)
    schedule = relationship("Schedule", back_populates="cars")
    seats = relationship("Seat", back_populates="car")


class Seat(Base):
    __tablename__ = "seat"
    id = Column(Integer, primary_key=True)
    carid = Column(Integer, ForeignKey("car.id"))
    car = relationship("Car", back_populates="seats")
    ticket = relationship("Ticket", back_populates="seat", uselist=False)


class Ticket(Base):
    __tablename__ = "ticket"
    id = Column(Integer, primary_key=True)
    seatid = Column(Integer, ForeignKey("seat.id"))
    price = Column(Numeric(10, 2))
    seat = relationship("Seat", back_populates="ticket")
