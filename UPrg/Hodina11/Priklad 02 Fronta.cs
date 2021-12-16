// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

using System;

namespace Priklad_02_Fronta
{
    class Program
    {
        private const int MAX_LENGTH = 100;

        private struct RingBuffer //a) cyklicka fronta
        {
            public int[] buffer;
            public int start;
            public int end;
            public int count;
        }

        private static RingBuffer RingBuffer_Create()
        {
            RingBuffer rb;
            rb.buffer = new int[MAX_LENGTH];
            rb.start = rb.end = rb.count = 0;

            return rb;
        }

        private static void RingBuffer_Enqueue(ref RingBuffer rb, int el)
        {
            if (rb.count != MAX_LENGTH)
            {
                rb.count++;
                if (rb.end == MAX_LENGTH - 1)
                {
                    rb.buffer[rb.end] = el;
                    rb.end = 0;
                }
                else
                    rb.buffer[rb.end++] = el;
            }
        }

        private static int RingBuffer_Dequeue(ref RingBuffer rb)
        {
            if (RingBuffer_IsEmpty(rb))
                throw new IndexOutOfRangeException();

            int item = 0;         
            rb.count--;

            if (rb.start == MAX_LENGTH - 1)
            {
                item = rb.buffer[rb.start];
                rb.start = 0;
            }
            else
                item = rb.buffer[rb.start++];

            return item;
        }

        private static int RingBuffer_Front(RingBuffer rb)
        {
            return rb.buffer[rb.start];
        }

        private static bool RingBuffer_IsEmpty(RingBuffer rb)
        {
            return rb.count == 0;
        }

        private static void RingBuffer_Write(RingBuffer rb)
        {
            int start = rb.start;
            for (int i = 0; i < rb.count; i++)
            {
                if (i == rb.count - 1)
                    Console.WriteLine(rb.buffer[start % 100]);
                else
                    Console.Write("{0} ", rb.buffer[start % 100]);
                start++;
            }
        }
        
        private static void RingBuffer_Test()
        {
            RingBuffer buff = RingBuffer_Create();

            for (int i = 0; i < 50; i++)
                RingBuffer_Enqueue(ref buff, i);

            Console.WriteLine("IsEmpty: {0}, expected False, count: {1}, start: {2} , end: {3}", RingBuffer_IsEmpty(buff), buff.count, buff.start, buff.end);
            RingBuffer_Write(buff);

            for (int i = 0; i < 50; i++)
                RingBuffer_Dequeue(ref buff);

            Console.WriteLine("IsEmpty: {0}, expected True, count: {1}, start: {2} , end: {3}", RingBuffer_IsEmpty(buff), buff.count, buff.start, buff.end);

            for (int i = 0; i < 100; i++)
                RingBuffer_Enqueue(ref buff, i);

            Console.WriteLine("IsEmpty: {0}, expected False, count: {1}, start: {2} , end: {3}", RingBuffer_IsEmpty(buff), buff.count, buff.start, buff.end);
            RingBuffer_Write(buff);

            for (int i = 0; i < 100; i++)
                RingBuffer_Dequeue(ref buff);

            Console.WriteLine("IsEmpty: {0}, expected True, count: {1}, start: {2} , end: {3}", RingBuffer_IsEmpty(buff), buff.count, buff.start, buff.end);
        }

        private struct SQueue //b) fronta s posunem
        {
            public int[] elements;
            public int start;
            public int end;
        }

        private static SQueue SQueue_Create()
        {
            SQueue sQueue;
            sQueue.elements = new int[MAX_LENGTH];
            sQueue.start = sQueue.end = 0;

            return sQueue;
        }
        
        private static void SQueue_Enqueue(ref SQueue sQueue, int el)
        {
            if (sQueue.end == MAX_LENGTH && SQueue_Count(sQueue) != 100)
            {             
                if (!SQueue_IsEmpty(sQueue))
                {
                    int i = 0;
                    for (int x = sQueue.start; x < sQueue.end; x++)
                    {
                        sQueue.elements[i] = sQueue.elements[x];
                        i++;
                    }

                    sQueue.start = 0;
                    sQueue.end = i;
                }
                else
                    sQueue.start = sQueue.end = 0;
            }
            sQueue.elements[sQueue.end++] = el;
        }

        private static int SQueue_Dequeue(ref SQueue sQueue)
        {
            if (SQueue_IsEmpty(sQueue))
                throw new IndexOutOfRangeException();

            return sQueue.elements[sQueue.start++];
        }

        private static int SQueue_Front(SQueue sQueue)
        {
            return sQueue.elements[sQueue.start];
        }

        private static bool SQueue_IsEmpty(SQueue sQueue)
        {
            return sQueue.start == sQueue.end;
        }

        private static void SQueue_Write(SQueue sQueue)
        {
            for (int i = sQueue.start; i < sQueue.end; i++)
            {
                if (i == sQueue.end - 1)
                    Console.WriteLine(sQueue.elements[i]);
                else
                    Console.Write("{0} ", sQueue.elements[i]);
            }
        }

        private static int SQueue_Count(SQueue sQueue)
        {
            return sQueue.end - sQueue.start;
        }

        private static void SQueue_Test()
        {
            SQueue sQueue = SQueue_Create();
            for (int i = 0; i < 50; i++)
                SQueue_Enqueue(ref sQueue, i);

            Console.WriteLine("IsEmpty: {0}, expected False, start: {1} , end: {2}", SQueue_IsEmpty(sQueue), sQueue.start, sQueue.end);
            SQueue_Write(sQueue);

            for (int i = 0; i < 50; i++)
                SQueue_Dequeue(ref sQueue);

            Console.WriteLine("IsEmpty: {0}, expected True, start: {1} , end: {2}", SQueue_IsEmpty(sQueue), sQueue.start, sQueue.end);

            for (int i = 0; i < 100; i++)
                SQueue_Enqueue(ref sQueue, i);

            Console.WriteLine("IsEmpty: {0}, expected False, start: {1} , end: {2}", SQueue_IsEmpty(sQueue), sQueue.start, sQueue.end);
            SQueue_Write(sQueue);

            for (int i = 0; i < 100; i++)
                SQueue_Dequeue(ref sQueue);

            Console.WriteLine("IsEmpty: {0}, expected True, start: {1} , end: {2}", SQueue_IsEmpty(sQueue), sQueue.start, sQueue.end);
        }

        private struct PQueue //c) prioritni fronta
        {
            public RingBuffer[] dQueues;
            public int count;
            public int d;
            public int highestPriority;
        }

        private static PQueue PQueue_Create(int d)
        {
            PQueue pQueue;
            pQueue.count = 0;
            pQueue.highestPriority = -1;
            pQueue.d = d;
            pQueue.dQueues = new RingBuffer[d];

            for (int i = 0; i < d; i++)
                pQueue.dQueues[i] = RingBuffer_Create();

            return pQueue;
        }

        private static void PQueue_Enqueue(ref PQueue pQueue, int el)
        {
            if (pQueue.count == MAX_LENGTH)
                return;
                
            pQueue.count++;

            int priority = Math.Abs(el % pQueue.d);

            if (priority > pQueue.highestPriority)
                pQueue.highestPriority = priority;

            RingBuffer_Enqueue(ref pQueue.dQueues[priority], el);
        }

        private static int PQueue_Dequeue(ref PQueue pQueue)
        {
            if (PQueue_IsEmpty(pQueue))
                throw new IndexOutOfRangeException();

            int highestPriority = pQueue.highestPriority;
            int el = RingBuffer_Dequeue(ref pQueue.dQueues[highestPriority]);
            pQueue.count--;

            if (pQueue.count == 0)
                pQueue.highestPriority = -1;
            else
            {
                if (RingBuffer_IsEmpty(pQueue.dQueues[highestPriority]))
                {
                    for (int i = highestPriority - 1; i >= 0; i--)
                    {
                        if (!RingBuffer_IsEmpty(pQueue.dQueues[i]))
                        {
                            pQueue.highestPriority = i;
                            break;
                        }
                    }
                }
            }

            return el;
        }
        
        private static int PQueue_Front(PQueue pQueue)
        {
            return RingBuffer_Front(pQueue.dQueues[pQueue.highestPriority]);
        }

        private static bool PQueue_IsEmpty(PQueue pQueue)
        {
            return pQueue.count == 0;
        }

        private static void PQueue_Write(PQueue pQueue)
        {
            for (int i = pQueue.d - 1; i >= 0; i--)
            {
                if (RingBuffer_IsEmpty(pQueue.dQueues[i]))
                    Console.WriteLine("{0}: ", i);
                else
                {
                    Console.Write("{0}: ", i);
                    RingBuffer_Write(pQueue.dQueues[i]);
                }
            }
        }

        private static void PQueue_Test()
        {
            Random r = new Random();
            PQueue pQueue = PQueue_Create(5);

            Console.WriteLine("PQueue IsEmpty: {0}, expected True", PQueue_IsEmpty(pQueue));

            for (int i = 0; i < 90; i++)
                PQueue_Enqueue(ref pQueue, r.Next(-200, 200));
            
            PQueue_Write(pQueue);
            Console.WriteLine("Front: {0}", PQueue_Front(pQueue));

            for (int i = 0; i < 80; i++)
                PQueue_Dequeue(ref pQueue);
            
            PQueue_Write(pQueue);
            Console.WriteLine("Front: {0}", PQueue_Front(pQueue));

            for (int i = 0; i < 20; i++)
                PQueue_Enqueue(ref pQueue, r.Next(-200, 200));

            PQueue_Write(pQueue);

            Console.WriteLine("PQueue IsEmpty: {0}, expected False", PQueue_IsEmpty(pQueue));
        }

        private static void Main(string[] args)
        {
            PQueue_Test();
        }
    }
}
